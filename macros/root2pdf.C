#include "TGraph.h"
#include "TKey.h"
#include "TProfile.h"
#include "K3Control.h"
#include "K3Ana.h"
#include "K4Talk.h"


Int_t counter = -1;
void Loop(TDirectory *, K4Talk *, Int_t);

int main(int argc, char**argv) {
     gROOT->SetBatch();

     const char * iname;
     if (argc < 2) {
	  gROOT->Fatal("main", "Expected root file.\nHave to exit. Try again.\n");
     } else {
	  iname = argv[1];
     }

     Int_t nmax = 1000000; //max drawn objects
     if (argc > 2) sscanf(argv[2], "%d", &nmax);

     TFile * file = new TFile(iname);
     TString pdfname = Form("%s.pdf", iname);

    
     K4Talk::Style();
     TCanvas * canvas = new TCanvas("Kaloyan Krastev(LPSC)", "Si-W ECAL Software",
				    1920, 1080);
     K4Talk & lilfjdvsd = K4Talk::Instance(pdfname, canvas);
     K4Talk * talk = &lilfjdvsd;
     talk->SetPrint();
     talk->Slide(iname);
     talk->Slide("ECAL sim/rec");
     talk->Draw("~/Myxa/mode/c++/root/slides/simrec.slide");
     talk->Slide("ECAL reconstructed to simulated hit relation");
     talk->Draw("~/Myxa/mode/c++/root/slides/relation.slide");

     Loop(file, talk, nmax);
     talk->SetTravail();
     talk->End();
    
     delete file;
     delete canvas;
     return 0;
}




void Loop(TDirectory * directory, K4Talk * talk, Int_t nmax) 
{
     TString jump = directory->GetName();
     talk->Info("Loop", "jump in %s", jump.Data());
     TList * list = directory->GetListOfKeys();
     TIter * iter = new TIter(list);
     TKey * key;

     Int_t nmin = 1;

     while ((key = (TKey *)iter->Next()) && counter < nmax) {
	  counter ++;
	  TString classname = key->GetClassName();
	  if (classname == "TDirectoryFile") {
	       TDirectory * sub = dynamic_cast<TDirectoryFile *>(key->ReadObj());
	       Loop(sub, talk, nmax);
	  } else if (classname == "K3Control") {
	       K3Control * control = dynamic_cast<K3Control *>(key->ReadObj());
	       talk->Info("Loop", "Got control:");
	       talk->Info("Loop", control->GetName());
	       talk->DrawControl(control);
	  } else if (classname == "TH1F") {
	       TH1F * h1f = dynamic_cast<TH1F *>(key->ReadObj());
	       Int_t n = Int_t(h1f->GetEntries());
	       if (n < nmin) continue;
	       talk->Slide();
	       talk->Info("Loop", "%d entries", n);	    
	       talk->Draw(h1f);
	  } else if (classname == "TH2F") {
	       TH2F * h2f = dynamic_cast<TH2F *>(key->ReadObj());
	       Int_t n = Int_t(h2f->GetEntries());
	       if (n < nmin) continue;
	       talk->Slide();
	       talk->Info("Loop", "%d entries", n);	    
	       talk->Draw(h2f, 1, 1, 1, "box");
	  } else if (classname == "TH3F") {
	       TH3F * h3f = dynamic_cast<TH3F *>(key->ReadObj());
	       Int_t n = Int_t(h3f->GetEntries());
	       if (n < nmin) continue;
	       talk->Slide();
	       talk->Info("Loop", "%d entries", n);	    
	       talk->Draw(h3f, 1, 1, 1, "iso");
	  } else if (classname == "TProfile") {
	       TProfile * h2f = dynamic_cast<TProfile *>(key->ReadObj());
	       Int_t n = Int_t(h2f->GetEntries());
	       if (n < nmin) continue;
	       talk->Slide();
	       talk->Info("Loop", "%d entries", n);	    
	       talk->Draw(h2f);
	  } else if (classname == "TGraph") {
	       TGraph * h2f = dynamic_cast<TGraph *>(key->ReadObj());
	       if (h2f->GetMean() == 0) continue;
	       talk->Slide();
	       talk->Info("Loop", "entries");	    
	       talk->Draw(h2f, 1, 1, 1, "ap");
	  } else {
	       talk->Warning("Loop", "Unforceen class %s", classname.Data());
	  }
     }  

     delete iter;

}

