/* belezhki
- da snimam kaskad
- da slozha danni i MC zaedno


*/

#include "TApplication.h"
#include "TChain.h"
#include "TF1.h"
#include "TF2.h"
#include "TFile.h"
#include "TGraph2D.h"
#include "TGraphErrors.h"
#include "TGraph2DErrors.h"
#include "TLorentzVector.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TStyle.h"
#include "TSystem.h"
#include "K3Control.h"
#include "K3Space.h"
#include "K4Stack.h"
#include "K5Event.h"

const Double_t threshold = 0.6;//minimum cell energy, MIP
//const Double_t alpha[3] = {1.1, 2, 2.7};//compensation coefficients
const Double_t alpha[3] = {1, 2, 3};//compensation coefficients
const Double_t beta = 250;//MIP/GeV
const Double_t gamm = 7000;//MIP/GeV
const Double_t offsetx = 17.2; //save distance in x from the edge of the detector and gaps
const Double_t offsety = 12.76; //save distance in y from the edge of the detector and gaps
const Double_t windowmin = 0.8;
const Double_t windowmax = 1.2;

const Double_t W0 = 5;//log parameter
const Double_t epsilon = 1e-5;
const Double_t mepsilon = 1e5;

const TVector2 __nula(0, 0);
const TVector3 ___nula(0, 0, 0);
TClonesArray*position;
TVector3 ___bclin;//baricenter of the shower

Bool_t         Compensate(K5Event*event, Int_t h, Double_t&energy, TVector3&___position);
void           DoShot(TClonesArray*ecal, TString shotfn);
Double_t       Distance(Double_t x, Double_t y, TF1*f);
Double_t       Distance(TLorentzVector*hit, K5Track track);

Int_t main(Int_t argc, char**argv) {

    const char*treefn;
    Int_t runentrymax = 1000000;
    Bool_t visualise = kFALSE;
    Bool_t analize = kTRUE;
    analize = kFALSE;
    if (argc > 1) treefn = argv[1];
    else Error("main", "Need tree file name as first argument. Has to exit.");
    if (argc < 2) return 1;
    if (argc > 2) sscanf(argv[2], "%d", &runentrymax);
    if (argc > 3) visualise = 0;


    TString geomfn = treefn;
    TString shotfn = treefn;
    TString controlfn = treefn;
    TString controlfnbackup = treefn;
    geomfn.ReplaceAll("root", "geom.root");
    shotfn.ReplaceAll("root", "shot.root");
    controlfn.ReplaceAll("root", "control.root");
    controlfnbackup.ReplaceAll("root", "temp.root");
    

    Info("main", "Gonna read a tree from %s", treefn);
    K5Event*event = 0;
    TChain*T = new TChain("test");
    Info("main", "Read %d", T->Add(treefn));
    T->SetBranchAddress("event", &event);


    //    geomfn = "~/root/geometry.root";
    Info("main", "Gonna get the geometry from %s", geomfn.Data());
    TFile geomf(geomfn);
    position = (TClonesArray*)geomf.Get("geometry");
    Double_t x_, y_, z_;
    Double_t x_min, y_min, z_min;
    x_min = y_min = z_min = 1e4;
    Double_t x_max, y_max, z_max;
    x_max = y_max = z_max = -1e4;

    //    for (Int_t i = 0; i < K5Hit::fNumLayer * K5Hit::fNumRow * K5Hit::fNumColumn; ++i) {
    for (Int_t i = 0; i < kNumLayer * kNumRow * kNumColumn; ++i) {
	TLorentzVector*v4 = (TLorentzVector*)position->At(i);
	
	x_ = v4->X();
	y_ = v4->Y();
	z_ = v4->Z();
	
	if (x_ == 0. && y_ == 0. && z_ == 0.) continue;
	
	x_min = (x_ < x_min) ? x_ : x_min;
	x_max = (x_ > x_max) ? x_ : x_max;
	y_min = (y_ < y_min) ? y_ : y_min;
	y_max = (y_ > y_max) ? y_ : y_max;
	z_min = (z_ < z_min) ? z_ : z_min;
	z_max = (z_ > z_max) ? z_ : z_max;
    }
    Info("main", "Got geometry: x = {%f;%f}, y = {%f;%f}, z = {%f;%f}", x_min, x_max, y_min, y_max, z_min, z_max);
    geomf.Close();

    const Int_t treeentries = (Int_t)T->GetEntries();

    TF1*f_x_z = new TF1("f_x_z", "[0]*x+[1]", z_min - 10, z_max + 10);
    TF1*f_y_z = new TF1("f_y_z", "[0]*x+[1]", z_min - 10, z_max + 10);
    TClonesArray*ecal = new TClonesArray("TLorentzVector", 10);


    Int_t good;//number of calo hits above threshold
    Int_t runentry;
    Int_t ntrack; 
    //    Int_t column;
    //    Int_t row;
    //    Int_t layer;

    Double_t eHit;//cell energy
    Double_t eeCor;// corrected energy
    Double_t eeRel;// corrected energy/ beam energy;

    //    Double_t mean;
    //    Double_t sigma;
    //    Double_t distance;
    Double_t disperse;
    //    Double_t magnitude;
    //    Double_t transmag;
    //    Double_t size;
    Double_t angle;//ref
    Double_t wlin;//linear weight
    Double_t wlinsum;//sum of all weights
    Double_t dlinx;//closest distance fromt the track to the barycenter
    Double_t dliny;//closest distance fromt the track to the barycenter
   

    TVector3 ___position;//cell position
    //    TVector3 ___bclin;//baricenter of the shower

    TF1*gapyfunction = new TF1("gapyfunction", "1-[0]*exp(-0.5*((x-[1])/[2])**2)");
    TF1*gapx1function = new TF1("gapx1function", "1-[0]*exp(-0.5*((x-[1])/[2])**2)");
    TF1*gapx2function = new TF1("gapx2function", "1-[0]*exp(-0.5*((x-[1])/[2])**2)");
    TF1*mapyfunction = new TF1("mapyfunction", "1-[0]*exp(-0.5*((x-[1])/[2])**2)");
    TF1*mapx1function = new TF1("mapx1function", "1-[0]*exp(-0.5*((x-[1])/[2])**2)");
    TF1*mapx2function = new TF1("mapx2function", "1-[0]*exp(-0.5*((x-[1])/[2])**2)");

    Double_t gapyvalue = -8.55;
    gapyfunction->SetParameters(0.223, gapyvalue, 2.74);

    Double_t gapx1value = -30.46;
    gapx1function->SetParameters(0.12, gapx1value, 4.85);

    Double_t gapx2value = 31.86;
    gapx2function->SetParameters(0.15, gapx2value, 4.27);

    //    Double_t mapyvalue = -8.78;
    mapyfunction->SetParameters(0.307, gapyvalue, 2.817);

    //    Double_t mapx1value = -30.58;
    mapx1function->SetParameters(0.18, gapx1value, 4.026);

    //    Double_t mapx2value = 31.77;
    mapx2function->SetParameters(0.18, gapx2value, 3.898);


    K5Track*track;
    K5Track crack;

    Double_t x_coordinate[55]; 
    for (Int_t i = 0; i < 55; ++i) 
	x_coordinate[i] = Double_t(i) * 4 - 110;


    Double_t y_coordinate[16] = {-110,-69.5,-59.5,-49.5,-39.5,-29.5,-19.5,-9.5,-8.65,2.65,12.65,22.65,32.65,42.65,52.65,110};
    Double_t z_coordinate[33] = {750, 763, 765, 773, 776, 784, 786, 794, 797, 805, 807, 818, 822, 831, 835, 845, 848, 858, 862, 871, 875, 887, 892, 904, 909, 920, 925, 936, 941, 952, 957, 962, 975};


    TFile controlf(controlfnbackup, "RECREATE");

    K3Control*C = 0;
    K3Space*S = 0;

    //    Int_t maxeventstoprocess = Int_t(1e8);

    Bool_t debug;
    Bool_t firstEvent = kTRUE;
    Bool_t firstCaloEvent = kTRUE;
    Bool_t shot = kTRUE;
    TString EB;
    Double_t oldEnergyBeam = 0;
    runentry = 0;

    for (Int_t entry = 0; entry < treeentries;// && entry < maxeventstoprocess; 
	 entry++) {
	if (firstEvent) debug = 1;
	else debug = 0;
	
	T->GetEntry(entry);

	if (debug && C) {
	    if (!event) Info("debug", "!event");
	    else Info("debug", "run %d, event %d", event->fRunNumber, event->fEventNumber);
	}

	if (event->fBeamEnergy - oldEnergyBeam > 1.) {//new beam energy
	    Info("main", "beam energy changed %f -> %f GeV (run %d)", oldEnergyBeam, event->fBeamEnergy, event->fRunNumber);

	    EB = Form("%.0f", event->fBeamEnergy);

	    runentry = 0;
	    if (C) {
		controlf.cd();
		C->Write();
		delete C;
	    }

	    //	    C = new K3Control(Form("test%s",EB.Data()), Form("%d", event->fRunNumber));
	    //if (C.exist -> open it)

	    C = new K3Control(Form("test%s",EB.Data()), EB.Data());
	    Info("main", "created a new control %s %s", C->GetName(), C->GetTitle());
	    Info("main", "processing entry %d, runentry %d, runentrymax %d, treeentries %d",//, maxeventstoprocess %d", 
		 entry, runentry, runentrymax, treeentries);//, maxeventstoprocess);


	    C->Book(1, "h1ee", "", "energy, GeV", "events", "", 44, 0, 50.);
	    C->Book(1, "h1eecor", "", "corrected energy, GeV", "events", "", 44, 0, 50.);
	    C->Book(1, "h1eerel", "", "energy/energyBeam", "events", "", 44, 0, 1.5);
	    C->Book(1, "h1disperse", "", "shower dispersion, mm", "events", "", 33, 7, 20.);
	    
	    C->Book(3, "h3meansigma", "", "mean", "sigma", "mean * sigma", 33, -10, 10, 22, 0, 10, 33, -33, 33);
	    C->Book(1, "h1deltalinx", "#Deltax, lin", "#Deltax,lin, mm", "events", "", 33, -7, 7.);
	    C->Book(1, "h1deltaliny", "#Deltay, lin", "#Deltay,lin, mm", "events", "", 33, -7, 7.);
	    C->Book(1, "h1angle", "angle", "angle, mrad", "events", "", 33, -300, 300);
	    C->Book(1, "h1deltae", "#DeltaE", "#DeltaE, GeV", "events", "", 33, -15, 15);
	    
//	    C->Book(3, "h3pads", "pad", "x, mm", "y, mm", "z, mm", 54, x_coordinate, 15, y_coordinate, 32, z_coordinate);
	    C->Book(3, "h3bclin", "lin", "x, mm", "y, mm", "z, mm",    33, -50, 40, 33, -30, 20, 33, 810, 900);
	    C->Book(2, "h2track", "track", "x, mm", "y, mm", "Events", 33, -50, 40, 33, -30, 20);
	    C->Book(3, "h3mom", "", "standard deviation", "skewness", "kurtosis", 22, 0, 30, 20, -1, 1.5, 20, -1, 1.5);
	    
	    C->Book(4, "p1gapx", "xenergy", "x, mm", "E/E, beam", "", 22, -40, 40.);
	    C->Book(4, "p1gapy", "yenergy", "y, mm", "E/E, beam", "", 22, -30, 20.);
    
	
	    C->Append("all;window;cherenkov;electron;corrected;safe");

	    C->Book(1, "h1beamenergy", "beam energy", "E, beam, GeV", "events", "", 33, 0, 60.);
	    C->Book(1, "h1ntrack", "ntrack", "number of tracks", "events", "", 4, -0.5, 3.5);
	    C->Book(1, "h1ehit", "hit energy", "E, hit, GeV", "hits", "", 22, 0, 4.);
	    C->Book(2, "h2eventrun", "eventrun", "event", "run", "", 22, 0, 100000, 22, 300190, 300680);
	    C->Book(2, "h2reflinx", "", "x, calo", "x, track", "Events", 50, -20, 20, 50, -20, 20);
	    C->Book(2, "h2refliny", "", "y, calo", "y, track", "Events", 50, -20, 20, 50, -20, 20);

	    //	    C->SetNumi(maxeventstoprocess > treeentries ? treeentries : maxeventstoprocess);
	    C->SetNumi(treeentries);

	    S = C->Space();
	    

	    S->Add("all");
	    S->Add("calo", epsilon);
	    S->Add("track");
	    S->Add("window", windowmin, windowmax);
	    S->Add("electron");
	    S->Add("contained");
	    S->Add("tcontained");
	    S->Add("ctrigger");
	    S->Add("btrigger");
	    S->Add("oogx");
	    S->Add("oogy");
	    S->Add("toogx");
	    S->Add("toogy");
	    S->Add("csafe");
	    S->Add("safe");

	} else if (runentry > runentrymax) {
	    entry += 100;
	    C->Entry(entry);
	    continue;
	}

	S->Off();
	S->On("all");
	//get track
	ntrack = event->GetNtrack();
	if (debug) Info("debug", "%d track", ntrack);
	if (debug) Info("debug", "Getting track");
	f_x_z->SetParameters(0, 0);
	f_y_z->SetParameters(0, 0);
	if (ntrack == 1) {
	    track = event->GetTrack();
	    if (track->IsCalculated()) {
		S->On("track");
		f_x_z->SetParameter(0, track->GetA());
		f_x_z->SetParameter(1, track->GetB());
		f_y_z->SetParameter(0, track->GetC());
		f_y_z->SetParameter(1, track->GetD());
	    } else Info("main", "Non-calculated track!"); 
	}


	//get hits
	ecal->Clear();
	good = 0;

	if (debug) Info("debug", "Genna get hits");
	event->fEnergy = 0;

	for (Int_t h = 0; h < event->GetNhit(); ++h) {
	    if (Compensate(event, h, eHit, ___position)) continue;
	    TClonesArray&e = *ecal;
	    new(e[good++]) TLorentzVector(___position.X(), ___position.Y(), ___position.Z(), eHit);
	    event->fEnergy += eHit;
	    C->Fill("h1ehit", eHit);
	}

	if (debug) Info("debug", "Got hits");
	if (debug) Info("debug", "event->fEnergy = %f", event->fEnergy);

	___bclin = ___nula;
	dlinx = dliny = wlinsum = 0;

	S->Check("calo", event->fEnergy);




	if (S->Is("calo")) {//calculate barycenter
	    for (Int_t h = 0; h < good; ++h) {
		TLorentzVector*ecalhit = (TLorentzVector*)ecal->At(h);
 		C->Fill("h3pads", ecalhit->X(), ecalhit->Y(), ecalhit->Z(), ecalhit->T());
 		wlin = ecalhit->T() / event->fEnergy;
		ecalhit->SetT(wlin);
 		___bclin += ecalhit->Vect() * wlin;
 		wlinsum += wlin;
	    }
	}


	if (debug) Info("debug", "Got barycenter");


	if (___bclin == ___nula || wlinsum == 0.) {
	    S->Off("calo");
	} else {//calculate distance barycemter - track
	    ___bclin *= 1. / wlinsum;
	    if (S->Is("track")) {
		//		dlinx = Distance(___bclin.Z(), ___bclin.X(), f_x_z);
		//		dliny = Distance(___bclin.Z(), ___bclin.Y(), f_y_z);
		dlinx = ___bclin.X() - f_x_z->Eval(___bclin.Z());
		dliny = ___bclin.Y() - f_y_z->Eval(___bclin.Z());

		if (debug) Info("main", "Distance to track: %f %f", dlinx, dliny);
	    }
	}
	
	disperse = angle = 0;

	if (analize) {
	    if (debug) Info("debug", "Gonna calculate shower direction");
	    crack.Reset();
	    //	    disperse = 0;
	    //	    angle = 0;
	    if (S->Is("calo") && good > 1) {
		Double_t*Xi = new Double_t[good]; 
		Double_t*Yi = new Double_t[good]; 
		Double_t*Zi = new Double_t[good]; 
		Double_t*Ei = new Double_t[good]; 
		//		Int_t nexthit = 0;
		for (Int_t h = 0; h < good; ++h) {
		    TLorentzVector*ecalhit = (TLorentzVector*)ecal->At(h);
		    Xi[h] = ecalhit->X();
		    Yi[h] = ecalhit->Y();
		    Zi[h] = ecalhit->Z();
		    Ei[h] = ecalhit->T();
		}

		TVectorD Vector_X = K5Event::LinearFit(good, Zi, Xi, Ei);
		TVectorD Vector_Y = K5Event::LinearFit(good, Zi, Yi, Ei);
		crack.SetABCD(Vector_X(1), Vector_X(0), Vector_Y(1), Vector_Y(0));
		delete[] Xi; 
		delete[] Yi; 
		delete[] Zi; 
		delete[] Ei; 
	    }

	    if (crack.IsCalculated()) {
		if (debug) Info("debug", "Gonna calculate transverse dispersion");
		for (Int_t h = 0; h < good; ++h) {
		    TLorentzVector*ecalhit = (TLorentzVector*)ecal->At(h);
		    disperse += Distance(ecalhit, crack) * ecalhit->T();
		}

		disperse /= wlinsum;
		
		if (S->Is("track")) {
		    TVector3*trackdirection = track->GetDirection();
		    TVector3*crackdirection = crack.GetDirection();
		    angle = trackdirection->Angle(*crackdirection);
		    delete trackdirection;
		    delete crackdirection;
		    if (angle > TMath::Pi() || angle < 0.) Error("main", "angle > pi");
		    if (angle > TMath::PiOver2()) angle -= TMath::Pi();
		}
		
	    }
	}

	if (debug) Info("debug", "selection...");


	if (S->Is("calo")) {
	    if (debug) Info("debug", "select events far away enough from dangerous zones");
	    if (kTRUE
		&&___bclin.X() > x_min + offsetx 
		&& ___bclin.X() < x_max - offsetx 
		&& ___bclin.Y() > y_min + offsety 
		&& ___bclin.Y() < y_max - offsety
		) S->On("contained");
	    if (kTRUE
		&& ___bclin.X() > gapx1value + offsetx 
		&& ___bclin.X() < gapx2value - offsetx
		) S->On("oogx");
	    if (kTRUE
		&& ___bclin.Y() > gapyvalue + offsety
		) S->On("oogy");
	}	    


	if (S->Is("track")) {
	    if (debug) Info("debug", "select track correspondingly");
	    if (kTRUE
		&& f_x_z->Eval(___bclin.Z()) > x_min + offsetx 
		&& f_x_z->Eval(___bclin.Z()) < x_max - offsetx
		&& f_y_z->Eval(___bclin.Z()) > y_min + offsety 
		&& f_y_z->Eval(___bclin.Z()) < y_max - offsety
		) S->On("tcontained");
	    if (kTRUE
		&& f_x_z->Eval(___bclin.Z()) > gapx1value + offsetx 
		&& f_x_z->Eval(___bclin.Z()) < gapx2value - offsetx 
		) S->On("toogx");
	    if (kTRUE
		&& f_y_z->Eval(___bclin.Z()) > gapyvalue + offsety
		) S->On("toogy");
	}


	if (event->IsMC()) eeCor = event->fEnergy * 
			       (1. / mapyfunction->Eval(___bclin.Y())) * 
			       (1. / mapx1function->Eval(___bclin.X())) * 
			       (1. / mapx2function->Eval(___bclin.X()));
	else eeCor = event->fEnergy * 
		 (1. / gapyfunction->Eval(___bclin.Y())) * 
		 (1. / gapx1function->Eval(___bclin.X())) * 
		 (1. / gapx2function->Eval(___bclin.X()));

	eeRel = eeCor / event->fBeamEnergy;
	if (debug) Info("main","IsMC() = %d, ee = %f, eeCor = %f, eeRel = %f", 
			event->IsMC(), event->fEnergy, eeCor, eeRel);

	S->Check("window", eeRel);
	if (event->fCherenkovTrigger) S->On("ctrigger");
	if (event->fBeamTrigger) S->On("btrigger");


	if (kTRUE
	    && S->Is("calo") 
	    && S->Is("window") 
	    //	    && S->Is("ctrigger")
	    && S->Is("btrigger") 
	    ) S->On("electron"); 

	if (kTRUE
	    && S->Is("contained") 
	    && S->Is("oogx") 
	    && S->Is("oogy")
	    ) S->On("csafe");

	if (kTRUE
	    && S->Is("csafe") 
	    && S->Is("tcontained") 
	    && S->Is("toogx") 
	    && S->Is("toogy")
	    ) S->On("safe");


	if (S->Is("electron") && S->Is("safe") && event->fBeamEnergy > 0. && shot) {
	    DoShot(ecal, shotfn);
	    shot = kFALSE;
	}
	

	if (debug) Info("debug", "Fill histograms...");
	C->Fill("h1ntrack", ntrack);  
	C->Fill("h1beamenergy", event->fBeamEnergy);
	C->Fill("h2eventrun", event->fEventNumber, event->fRunNumber);

	if (S->Is("calo")) {
	    if (___bclin == ___nula) Warning("mean", "___bclin == ___nula"); 

	    C->Fill("h1eerel+all", eeRel);
	    C->Fill("h1eecor+all", eeCor);
	    C->Fill("h1ee+all", event->fEnergy);
	    C->Fill("h1disperse+all", disperse);
	    C->Fill("h3bclin+all", ___bclin.X(), ___bclin.Y(), ___bclin.Z());

	    if (S->Is("window")) {
		C->Fill("h1eerel+window", eeRel);
		C->Fill("h1eecor+window", eeCor);
		C->Fill("h3bclin+window", ___bclin.X(), ___bclin.Y(), ___bclin.Z());
	    }
	    
	    if (S->Is("ctrigger")) {
		C->Fill("h1eerel+cherenkov", eeRel);
		C->Fill("h1eecor+cherenkov", eeCor);
		C->Fill("h3bclin+cherenkov", ___bclin.X(), ___bclin.Y(), ___bclin.Z());
	    }
	}


	if (S->Is("electron")) {
	    C->Fill("h1eerel+electron", eeRel);
	    C->Fill("h1eecor+electron", eeCor);
	    C->Fill("h3bclin+electron", ___bclin.X(), ___bclin.Y(), ___bclin.Z());
	    
	    if (S->Is("oogy")) {
		C->Fill("p1gapx+electron", ___bclin.X(), event->fEnergy / event->fBeamEnergy);
		C->Fill("p1gapx+corrected", ___bclin.X(), eeRel);
	    }
	    if (S->Is("oogx")) {
		C->Fill("p1gapy+electron", ___bclin.Y(), event->fEnergy / event->fBeamEnergy);
		C->Fill("p1gapy+corrected", ___bclin.Y(), eeRel);
	    }
	    
	    C->Fill("h1disperse+electron", disperse);
	    C->Fill("h1deltae+electron", 100 * (event->fEnergy - event->fBeamEnergy) / event->fEnergy);
	    C->Fill("h1deltae+corrected",100 * (eeCor - event->fBeamEnergy) / eeCor);
	    if (S->Is("csafe")) C->Fill("h1deltae+safe", 100 * (eeCor - event->fBeamEnergy) / eeCor);
	    
	    if (S->Is("track")) {
		C->Fill("h1angle+electron", angle * 1000);
		C->Fill("h1deltalinx+electron", dlinx);
		C->Fill("h1deltaliny+electron", dliny);
		
		C->Fill("h2track+electron", f_x_z->Eval(___bclin.Z()), f_y_z->Eval(___bclin.Z()));
		if (S->Is("oogy")) C->Fill("h2reflinx", ___bclin.X(), f_x_z->Eval(___bclin.Z()));
		if (S->Is("oogx")) C->Fill("h2refliny", ___bclin.Y(), f_y_z->Eval(___bclin.Z()));
		
		if (S->Is("safe")) {
		    C->Fill("h1deltalinx+safe", dlinx);
		    C->Fill("h1deltaliny+safe", dliny);
		    C->Fill("h1angle+safe", angle * 1000);

		    C->Fill("h3bclin+safe", ___bclin.X(), ___bclin.Y(), ___bclin.Z());
		    C->Fill("h2track+safe", f_x_z->Eval(___bclin.Z()), f_y_z->Eval(___bclin.Z()));
		    C->Fill("h1disperse+safe", disperse);
		}
	    }
	}

	if (S->Is("calo")) firstCaloEvent = 0;
	firstEvent = 0;
	if (S->Is("electron") && S->Is("track")) {
	    if (debug) Info("main", "runentry++");
	    runentry++;
	}
	S->FillCorrelationMatrix();
	C->Entry(entry);
	oldEnergyBeam = event->fBeamEnergy;
	//end of event loop
    }

    controlf.cd();
    C->Write();
    delete C;

    Info("main", "control written");

    delete f_x_z;
    delete f_y_z;

    Info("main", "f_t deleted");

    ecal->Clear();
    delete ecal;

    Info("main", "ecal deleted");

    controlf.Close();
    gSystem->Exec(Form("mv -v %s %s", controlfnbackup.Data(), controlfn.Data()));

    return 0;
}


Double_t Distance(Double_t x, Double_t y, TF1*f) {
    Double_t a = f->GetParameter(0);
    //    Double_t b = f->GetParameter(1);
    Double_t deltay = y - f->Eval(x);
    Double_t cosphi = 1 / TMath::Sqrt(1 + (a * a));

    //    Info("Distance", "cosphi=%f", cosphi);
	//    Double_t __y0 = f->Eval(x);
	//    Double_t __delta = f->Eval(x) - y0;

    return deltay * cosphi;
    
}


Bool_t Compensate(K5Event*event, Int_t h, Double_t&energy, TVector3&___position) {
    K5Hit*hit = event->GetHit(h);
    if (!hit) Error("Compensate", "!hit at %d", h);

    energy = hit->GetEnergy();
    if (energy == 0.) return kTRUE;
    if (event->IsMC()) energy *= gamm;
    if (energy < threshold) return kTRUE;

    //convert in GeV & correct for the absorber
    energy /= beta;
    if (hit->GetLayer() < 10) energy *= alpha[0];
    else if (hit->GetLayer() < 20) energy *=  alpha[1];
    else energy *= alpha[2];

    TLorentzVector*v4 = (TLorentzVector*)position->At(hit->GetCellNumber());
    ___position.SetXYZ(v4->X(), v4->Y(), v4->Z());
    return kFALSE;
}


void DoShot(TClonesArray*ecal, TString shotfn) { 
    TFile shotf(shotfn, "RECREATE");
    shotf.cd();
    ecal->Write("geometry", TObject::kSingleKey);
    shotf.Close();
    Info("DoShot", "Shot in %s", shotfn.Data());
}
 
Double_t Distance(TLorentzVector*hit, K5Track track) {
    Double_t dx = ( hit->X() - (track.GetA() * hit->Z() + track.GetB()) ) / TMath::Sqrt(1 + (track.GetA() * track.GetA()));
    Double_t dy = ( hit->Y() - (track.GetC() * hit->Z() + track.GetD()) ) / TMath::Sqrt(1 + (track.GetC() * track.GetC()));
    return TMath::Sqrt(dx * dx + dy * dy);
}
