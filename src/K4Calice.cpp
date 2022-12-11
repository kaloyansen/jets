//____________________________________________________________________
//
// process massive account of calice Si-W histograms
//

//____________________________________________________________________
//
// $Id$
// Author: kkrastev <kkrastev@>
// Update: 2009-11-30 20:36:03+0100
// Copyright: 2009 (C) kkrastev
//
#ifndef ROOT_K4Calice
#include "K4Calice.h"
#endif

//____________________________________________________________________
ClassImp(K4Calice);

//_________________________________________________________________________________________
void K4Calice::Initialize(Int_t min, Int_t max, Int_t gapfrom, Int_t gapto, Int_t runsperbin) {
    fMinRunNumber = fRunNumber = min;
    fMaxRunNumber = max;
    fInput = fOutput = 0;
    fInputFile = fOutputFile = 0;
    fGapFrom = 301000;
    fGapTo = 330000;
    fGapW = fGapTo - fGapFrom;
    fRunTitle = Form("if (rn > %d) rn += %d", fGapFrom, fGapW);
    fRunTitle = "run number";
    fRunsPerBin = runsperbin;
}

//________________
K4Calice::K4Calice() { this->Initialize(0, 999999, 1, 999998, 1); }

//__________________________________________________________________________________________________
K4Calice::K4Calice(Int_t min, Int_t max, Int_t gapfrom, Int_t gapto, Int_t runsperbin, TString option) {

    this->Initialize(min, max, gapfrom, gapto, runsperbin);

    TDatime datime;
    UInt_t date = datime.Get();
    TString file = Form("calice.%s.%d.root", option.Data(), date);
    TString link = Form("calice.%s.root", option.Data());
    gSystem->Unlink(link);
    gSystem->Unlink(file);
    gSystem->Symlink(file, link);
    fOutputFile = TFile::Open(file, "UPDATE");
    fOutput = fOutputFile;

    TString inputName;

    for (fRunNumber = fMinRunNumber; fRunNumber < fMaxRunNumber; fRunNumber++) {
	if (option.CompareTo("noise")) {
	    inputName = Form("/sps/ilc/kkrastev/cern/histos/histos/h_%d.root", fRunNumber);
	    if (gSystem->AccessPathName(inputName.Data())) continue;
	    fInputFile = TFile::Open(inputName);
	    if (!fInputFile || fInputFile->IsZombie()) continue;
	    fInput = fInputFile->GetDirectory("EmcCaliceTriggerProcessor");
	    fInput = fInputFile->GetDirectory("EmcSimpleHitSearch/ADCValues");
	    fInput = fInputFile->GetDirectory("EmcSimpleHitSearch/States");
	    fInput = fInputFile->GetDirectory("EmcSimpleHitSearch/AverageNoise");
	    fInput = fInputFile->GetDirectory("EmcSimpleHitSearch/DeadCells");
	    fInput = fInputFile;
	    Info("K4Calice", "%d", fRunNumber);
	    gSystem->Exec("date");
	    this->Loop(option);
	    delete fInputFile;
	} else {
	    inputName = Form("/sps/ilc/kkrastev/cern/histos/histos/Noise_Run%d.root", fRunNumber);
	    if (gSystem->AccessPathName(inputName.Data())) continue;
	    fInputFile = TFile::Open(inputName);
	    if (!fInputFile || fInputFile->IsZombie()) continue;
	    fInput = fInputFile;
	    Info("K4Calice", "%d", fRunNumber);
	    gSystem->Exec("date");
	    this->Noise();
	    delete fInputFile;
	}
    }
}

//_________________
K4Calice::~K4Calice() {
    if (!fOutputFile) return;
    fOutputFile->Close();
    delete fOutputFile;
}

//________________________
void K4Calice::Synchronize() {//gets to the corresponding output directory
    TString fullpath = fInput->GetPath();
    TString path( (char*)strstr( fullpath, ":" ) );
    path.Remove(0, 2);

    //    Info("Synchronize", "to <%s>", path.Data());
    if (!fOutput) { Error("Synchronize", "!fOutput"); return; }

    fOutput = fOutputFile;
    TDirectory*success = fOutputFile->GetDirectory(path);
    if (!success) {
	//	Info("Synchronize", "%s not found", path.Data());
	TObjArray*array = path.Tokenize("/");
	Int_t d = 0;
	while (TObjString*objString = (TObjString*)array->At(d)) {
	    TString dir = objString->GetString();
	    //	    Info("Synchronize", "will make %s", dir.Data());
	    fOutputFile->cd();
	    fOutput->mkdir(dir.Data());
	    fOutput = fOutput->GetDirectory(dir.Data());
	    //	    fOutput->pwd();
	    d++;
	}
    } else fOutput = success;
}

//________________________
void K4Calice::Correlation() {
    fOutput->cd();
    TF1*gauss = new TF1("gauss","gaus",-500,500);
    TH2F*h2 = new TH2F(Form("%d", fRunNumber), Form("%d;index;index", fRunNumber), 30*9*36, 0, 30*9*36, 30*9*36, 0, 30*9*36);


    for (unsigned int layer = 0; layer < 30; layer++)//loop on PCBs
	for (unsigned int waf = 0; waf < 9; waf++)//loop on wafers
	    for (unsigned int cell1 = 0; cell1 < 36; cell1++) {//loop on cells
		TString hname = Form("p_Ped_l%d_waf%d_cell%d", layer, waf, cell1);
		TH1F*h1 = (TH1F*)fInput->FindObjectAny(hname);
		if (!h1) continue;
		if (h1->GetEntries() > 0) {
		    h1->Fit("gauss","RQ0");
		    Float_t noise = gauss->GetParameter(2);
		    Int_t index = 9 * 36 * layer + 36 * waf + cell1;

		    for (unsigned int _layer = 0; _layer < 30; _layer++)//loop on PCBs
			for (unsigned int _waf = 0; _waf < 9; _waf++)//loop on wafers
			    for (unsigned int _cell1 = 0; _cell1 < 36; _cell1++) {//loop on cells
				TString _hname = Form("p_Ped_l%d_waf%d_cell%d", _layer, _waf, _cell1);
				TH1F*_h1 = (TH1F*)fInput->FindObjectAny(_hname);
				if (!_h1) continue;
				if (_h1->GetEntries() > 0) {
				    _h1->Fit("gauss","RQ0");
				    Float_t _noise = gauss->GetParameter(2);
				    Int_t _index = 9 * 36 * layer + 36 * waf + cell1;
				    h2->Fill(index, _index, noise * _noise);
				}
				delete _h1;
			    }
		}
		delete h1;
	    }

    delete gauss;
    fOutput->cd();
    h2->Write();//, kOverwrite);
}


//__________________
void K4Calice::Noise() {//loops through historams
    fOutput->cd();
    TF1*gauss = new TF1("gauss","gaus",-500,500);

    TGraph*g_pedestal = new TGraph(30*9*36);
    g_pedestal->SetName(Form("pedestal%d", fRunNumber));
    g_pedestal->SetTitle(Form("pedestal%d", fRunNumber));
    g_pedestal->GetXaxis()->SetTitle("Pad index");
    g_pedestal->GetYaxis()->SetTitle("R_{G} (ADC Counts)");

    TGraph*g_noise = new TGraph(30*9*36);
    g_noise->SetName(Form("noise%d", fRunNumber));
    g_noise->SetTitle(Form("noise%d", fRunNumber));
    g_noise->GetXaxis()->SetTitle("Pad index");
    g_noise->GetYaxis()->SetTitle("N_{G} (ADC Counts)");


    for (unsigned int layer = 0; layer < 30; layer++)//loop on PCBs
	for (unsigned int waf = 0; waf < 9; waf++)//loop on wafers
	    for (unsigned int cell1 = 0; cell1 < 36; cell1++) {//loop on cells
		TString hname = Form("p_Ped_l%d_waf%d_cell%d", layer, waf, cell1);
		TH1F*h1 = (TH1F*)fInput->FindObjectAny(hname);
		if (!h1) continue;
		if (h1->GetEntries() > 0) {
		    h1->Fit("gauss","RQ0");
		    Float_t pedestal = gauss->GetParameter(1);
		    Float_t noise = gauss->GetParameter(2);
		    Int_t index = 9 * 36 * layer + 36 * waf + cell1;
		    //		    Info("Noise", "%s %d", hname.Data(), index);
		    g_pedestal->SetPoint(index, index, pedestal);
		    g_noise->SetPoint(index, index, noise);
		}
		delete h1;
	    }

    delete gauss;
    fOutput->cd();
    g_pedestal->Write();//, kOverwrite);
    g_noise->Write();//, kOverwrite);
}

//_______________________________
void K4Calice::Loop(TString option) {//recursive loops
    Synchronize();
    TString path( (char*)strstr( fOutput->GetPath(), ":" ) );
    path.Remove(0, 2);


    //drop directories
    if (path.BeginsWith("EmcPedestalNoiseHistograms")) return;
    //    if (path.BeginsWith("EmcSimpleHitSearch")) return;
    //    if (path.BeginsWith("EmcCaliceTriggerProcessor")) return;

    if (!path.CompareTo("EmcSimpleHitSearch/Noise")) return;
    if (!path.CompareTo("EmcSimpleHitSearch/Signal")) return;
    if (!path.CompareTo("EmcSimpleHitSearch/SignalIndusedPedestalShift")) return;
    if (!path.CompareTo("EmcSimpleHitSearch/ADCValueAfterGlobalPedCorrection")) return;
    if (!path.CompareTo("EmcSimpleHitSearch/ADCValueAfterPedShCorr")) return;
    if (!path.CompareTo("EmcSimpleHitSearch/ADCValueBeforeGlobalPedCorrection")) return;

    //    Info("Loop", "read %s", path.Data());


    TList*list = fInput->GetListOfKeys();
    //    Int_t entries = list->GetEntries();
    TIter*iter = new TIter(list);
    TKey *key, *oldkey=0;

    while ((key = (TKey*)iter->Next())) {
	if (oldkey && !strcmp(oldkey->GetName(),key->GetName())) continue;
	TString classname = key->GetClassName();
	if (classname == "TDirectoryFile") {
	    fInput = dynamic_cast<TDirectory*>(key->ReadObj());
	    Loop(option);
	} else if (classname == "TH1F") {
	    TH1F*h1 = dynamic_cast<TH1F*>(key->ReadObj());
	    if (!option.CompareTo("profile")) {
		Teleprofile(h1);
	    } else if (!option.CompareTo("h2")) {
		Teleh2(h1);
	    } else {
		Error("Loop", "Unforseen option %s", option.Data());
	    }

	    delete h1;
	} else if (classname == "TH2F") { 
	    TH2F*h2 = dynamic_cast<TH2F*>(key->ReadObj());
	    TH1D*hx = h2->ProjectionX();
	    TH1D*hy = h2->ProjectionY();
	    if (!option.CompareTo("profile")) {
		Teleprofile(hx);
		Teleprofile(hy);
	    } else if (!option.CompareTo("h2")) {
		Teleh2(hx);
		Teleh2(hy);
	    } else {
		Error("Loop", "Unforseen option %s", option.Data());
	    }

	    delete h2;
	    
	} else if (classname == "TGraph") { ;
	} else if (classname == "TGraphErrors") { ;
	} else Error("Loop", "classname %s", classname.Data());
    }

    delete iter;
}

//________________________
TH1*K4Calice::Teleh2(TH1*h1) {//adds the run number as a second dimension
    TH1*nova = 0;
    if (!h1 || h1->GetEntries() == 0) return nova;

    TString name = h1->GetName();
    name += "__h2";

    TObject*obj = fOutput->FindObject(name.Data());
    //    fOutput->pwd();
    if (!obj) {
	Info("Teleport", "h2 %s", name.Data());
	fOutput->cd();
	nova = new TH2F(name, h1->GetTitle(),
			h1->GetXaxis()->GetNbins(),
			h1->GetBinLowEdge(1),
			h1->GetBinLowEdge(h1->GetNbinsX() + 1),
			(fMaxRunNumber - fMinRunNumber - fGapW + 1) / fRunsPerBin,
			fMinRunNumber + fGapW - 0.5,
			fMaxRunNumber + 0.5);
	nova->SetYTitle(fRunTitle);
    } else if (obj->IsA()->InheritsFrom("TH1")) nova = dynamic_cast<TH1*>(obj);
    else {
	Error("Teleport", "%s does not inherit from TH1", name.Data());
	return nova;
    }

    Int_t gapped = fRunNumber;
    if (fRunNumber < fGapFrom) gapped += fGapW;
    Int_t bin = gapped - fMinRunNumber - fGapW + 1;

    for (Int_t b = 0; b < h1->GetNbinsX() + 2; ++b) {
	Float_t value = h1->GetBinContent(b);
	if (value == 0) continue;
	//	nova->Info("Teleport", "%d %f", gapped, value);
	nova->SetBinContent(b, bin, value);
    }

    fOutput->cd();
    nova->Write(nova->GetName(), kOverwrite);

    return nova;
}


//_____________________________
TH1*K4Calice::Teleprofile(TH1*h1) {
    TProfile*nova = 0;
    if (!h1 || h1->GetEntries() == 0) return nova;

    TString name = h1->GetName();
    name += "__profile";

    TObject*obj = fOutput->FindObject(name.Data());
    //    fOutput->pwd();
    if (!obj) {
	Info("Teleport", "profile %s", name.Data());
	fOutput->cd();
	nova  = new TProfile(name, h1->GetTitle(),
			     (fMaxRunNumber - fMinRunNumber - fGapW + 1) / fRunsPerBin,
			     fMinRunNumber + fGapW - 0.5,
			     fMaxRunNumber + 0.5);
    } else if (obj->IsA()->InheritsFrom("TH1")) nova = dynamic_cast<TProfile*>(obj);
    else {
	Error("Teleport", "%s does not inherit from TH1", name.Data());
	return nova;
    }

    Int_t gapped = fRunNumber;
    if (fRunNumber < fGapTo) gapped += fGapW;

    for (Int_t b = 0; b < h1->GetNbinsX() + 2; ++b) {
	Float_t value = h1->GetBinContent(b);
	if (value == 0) continue;
	//	nova->Info("Teleport", "%d %f", gapped, value);
	nova->Fill(Float_t(gapped), value);
    }

    fOutput->cd();
    nova->Write(nova->GetName(), kOverwrite);
    return nova;
}


//____________________________________________________________________
//
// EOF
//
