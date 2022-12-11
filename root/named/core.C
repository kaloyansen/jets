/*
  Tools to manipulate tree or chain
*/
//#include <iostream.h>

#define FIT_MONITOR_FILE "fits/lastFit.ps"
#define Z_FIT_FILE "fits/fitZCut.root"
#define Y_FIT_FILE "fits/fitYh.root"
#define T_FIT_FILE "fits/fitTrig.root"
#define PANOPM_FILE "files/output/panopm/"


#define MC_DRAW_OPTION "HIST"
//#define MC_DRAW_OPTION "HIST,E1"
//#define MC_DRAW_OPTION "HIST,]["

#define ENERGY_COLOR kGray

//#define CONTROL_LOCATION "files/control/oldControl"
//#define CONTROL_LOCATION "/afs/desy.de/user/k/kaloyan/h1/oo/h1/root/files/control/oldControl"
#define CONTROL_LOCATION "/acsdisk/user/kaloyan/control/oldControl"
//#define COMBINED_LOCATION "files/control/"
#define COMBINED_LOCATION "/afs/desy.de/user/k/kaloyan/h1/oo/h1/root/files/control/"

#define WHERE_THE_FITS_ARE "fits/fits.root"
#define WHERE_THE_FITS_WILL_BE "fits/fits.new.root"

#define WHITE_SCRIPT "../config/whiteShit.zsh"
#define BLACK_AND_WHITE kFALSE
#define BACKGROUND_MARKER_STYLE kOpenTriangleUp








void coreLookAtChain(TString file,TString level="detector")
{
    TChain*chain=coreChain(file);
    TH1F*q2=new TH1F("q2","q2",10,0,1.5);
    TH1F*yh=new TH1F("yh","yh",10,0,1.5);
    TCanvas*can=new TCanvas("look","look");
    can->Divide(2,2);
    can->cd(1);
    chain->Draw("b_"+level+".h1Q2e>>q2");
    can->Update();
    can->cd(2);
    chain->Draw("b_"+level+".h1Yh>>yh");
    can->Update();
    can->cd(3);
    chain->Draw("b_"+level+".JetN()");
    can->cd(4);
    chain->Draw("b_"+level+".NNiceJets(-0.5,2.,7,7,5,5)");
    can->Update();
    delete chain;
}


TChain*coreChain(TString code)
{
    TChain*chain=new TChain("K3");
    TString input="";

    if (!code.CompareTo("data")) {
	input="files/k3/K3d06*.root";
    } else {
	input=code;
    }

    Info("coreChain","Adding %s",input.Data());
    chain->Add(input);
    return chain;
}




TString coreCut()
{
    Float_t cjc_0=463.8;
    Float_t lar_0=0.033;
    TString cut="";
    //    cut="b_detector.h1T0_CJC>363.8&&b_detector.h1T0_CJC<563.8" ;
    //    cut+="&&";
    //    cut+="b_detector.h1T0_LAr>-0.666&&b_detector.h1T0_LAr<0.733";   
    cut+="&&";
    cut+="b_detector->NNiceJets(-0.5,1.74,7.0,7.0,5.0,5.0)>2";
    cut+="&&";
    cut+="b_detector.h1VtxZ>-35.0&&b_detector.h1VtxZ<35.0";
    return cut;
}


void coreCreateEventList(Int_t st=0)
{

    TString cut="";
    if (st==76) {
	cut+="b_detector.fTriggers[76].Trigac==1";
    } else if (st==74) {
	cut+="b_detector.fTriggers[74].Trigac==1";
    } else {
	Error("coreCreateEventList","oops");
    }

    //    cut+=coreCut();
    coreCreateEventList("data",cut,"list.root");
}


void coreCreateEventList(TString input,TString cut,TString output)
{
    TBenchmark*bench=new TBenchmark();
    bench->Start("Total execution time"); 

    TChain*chain=coreChain(input);
    Info("coreCreateEventList","Creating event list %s",cut.Data());
    chain->Draw(">>evList",cut);
    TEventList*list=(TEventList*)gDirectory->Get("evList");

    TFile*file=new TFile(output,"recreate");
    list->Print();
    list->Write();
    file->Close();
    delete file;

    bench->Show("Total execution time");
    rEnd();
}








