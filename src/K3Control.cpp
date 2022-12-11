// Author: Kaloyan Kratsev <mailto:krastev@lpsc.in2p3.fr> 


#include "K3Control.h"


//______________________________________________________________________________
/* Begin_Html

   ky - ky

   End_Html */




ClassImp(K3Control)

K3Control::K3Control() : TNamed() { Ini(); }  
K3Control::K3Control(TString name,TString title) : TNamed(name, title) { Ini(); }
K3Control::~K3Control() 
{//    Info("~","dtor"); 
     if (fList) { fList->Clear(); delete fList; }
     if (fSpace) delete fSpace;
}

void K3Control::Ini() 
{//    Info("ctor","Create control %s %s ",fName.Data(),fTitle.Data());
     fLast = 0;
     fList = 0;
     fSpace = 0;
     SetAll();
}

void K3Control::SetAll(Int_t numi, Float_t lumi, Int_t ismc, Bool_t issim,
		       const char * steer)
{
     fNumi  = numi;
     fLumi  = lumi;
     fMC    = ismc;
     fSim   = issim;
     fSteer = steer;
}



void K3Control::Draw(Option_t* option) 
{ 
     if (!fSpace) return;
     fSpace->CorrelationMatrixHistogram()->Draw(option); 
}


void K3Control::Remember(const char*xTitle, const char*yTitle, const char*zTitle)
{
     if (!fList) fList = new TList();
     fList->SetOwner();
     if (!fLast) return;
     fLast->SetXTitle(xTitle);
     fLast->SetYTitle(yTitle);
     fLast->SetZTitle(zTitle);
     Freeze(0);
     fList->Add(fLast);
}

void K3Control::Freeze(bool frozen) 
{ 
     if (!fLast) return;
     fLast->SetBit(TH1::kCanRebin, !frozen); 
}

void K3Control::Book(Int_t dimension,
		     const char * name, const char * title, const char * xTitle, const char * yTitle, const char * zTitle,
		     Int_t nbinsx, Double_t xlow, Double_t xup,
		     Int_t nbinsy, Double_t ylow, Double_t yup,
		     Int_t nbinsz, Double_t zlow, Double_t zup)
{//    Info("Book", "calling constant bin histogram constructor");
     fLast = 0;
//     TH1 * h = 0;
     TString ime = Form("%s_%s", fName.Data(), name);
     if (dimension == 0) return;
     else if (dimension == 1) fLast = new TH1D(ime, title, nbinsx, xlow, xup);
     else if (dimension == 2) fLast = new TH2D(ime, title, nbinsx, xlow, xup, nbinsy, ylow, yup);
     else if (dimension == 3) fLast = new TH3D(ime, title, nbinsx, xlow, xup, nbinsy, ylow, yup, nbinsz, zlow, zup);
     else if (dimension == 4) fLast = new TProfile(ime, title, nbinsx, xlow, xup);
     else if (dimension == 5) fLast = new TProfile2D(ime, title, nbinsx, xlow, xup, nbinsy, ylow, yup);
     else if (dimension == 6) fLast = new TProfile3D(ime, title, nbinsx, xlow, xup, nbinsy, ylow, yup, nbinsz, zlow, zup);
     else Info("Book", "no %d dimension", dimension);
     Remember(xTitle, yTitle, zTitle);
}


// TH1*K3Control::BookArray(Int_t dimension,
// 			 const char* name, const char* title,
// 			 const char*xTitle, const char*yTitle, const char*zTitle,
// 			 Int_t nbinsx, const Double_t*xbins,
// 			 Int_t nbinsy, const Double_t*ybins,
// 			 Int_t nbinsz, const Double_t*zbins)
// {//    abandoned
//      TH1*h = 0;
//      TString ime = Form("%s_%s", fName.Data(), name);
//      if (dimension == 0) return h;
//      else if (dimension == 1) h = new TH1D(ime, title, nbinsx, xbins);
//      else if (dimension == 2) h = new TH2D(ime, title, nbinsx, xbins, nbinsy, ybins);
//      else if (dimension == 3) h = new TH3D(ime, title, nbinsx, xbins, nbinsy, ybins, nbinsz, zbins);
//      else if (dimension == 4) h = new TProfile(ime, title, nbinsx, xbins);
//      else if (dimension == 5) h = new TProfile2D(ime, title, nbinsx, xbins, nbinsy, ybins);
//      else if (dimension == 6) h = new TProfile3D(ime, title, nbinsx, xbins, nbinsy, ybins, nbinsz, zbins);
//      else Info("BookArray", "no %d dimension", dimension);
//      Remember(h, xTitle, yTitle, zTitle);
//      return h;
// }



TH1 * K3Control::Identify(TString name,
			  const char * project, const char * reproject)
{
     if (!fList) Error("Identify", "!fList");
     //    Info("Identify", "begin");
     TString find = Form("%s_%s", fName.Data(), name.Data());
     //    Info("Identify", "find formed %s", find.Data());
     //    fList->Print();
     //    Info("Identify", "searching for %s", find.Data());
     TH1 * id = (TH1 *)fList->FindObject(find.Data());
     //    Info("Identify", "search done");
     if (!id) {
	  //	Info("Identify", "has to return zero pointer for %s!",name.Data());
	  return id;
     } else {
	  //	Info("Identify", "id");
     }

     if (!project) {
	  //	Info ("Identify", "ok");
	  return id;
     } else {
	  //	Info ("Identify", "not ok");
     }

     TH2D*mother = (TH2D*)id;

     TString pro = project;
     if (!pro.CompareTo("x")) return mother->ProjectionX();
     else if (!pro.CompareTo("y")) return mother->ProjectionY();
     else {
	  TH3D*father = (TH3D*)id;
	  TString rep = project;
	  if (!reproject) {	    
	       return father->Project3D(project);
	  } else if (!rep.CompareTo("x")) {
	       TH2D * daughter = (TH2D *)father->Project3D("yx");
	       return daughter->ProjectionX();
	  } else if (!rep.CompareTo("y")) {
	       TH2D * daughter = (TH2D *)father->Project3D("zy");
	       return daughter->ProjectionX();
	  } else if (!rep.CompareTo("z")) {
	       TH2D * daughter = (TH2D *)father->Project3D("xz");
	       return daughter->ProjectionX();
	  } else Error("Identify", "reports invalid reproject option <%s>", reproject);
     }



     Error("Identify","should not get here");
     return id;
}



Int_t K3Control::Fill(TString name, Double_t x, Double_t y, Double_t z, Double_t w)
{
     Int_t bits = -1;
     if (fSpace) bits = fSpace->Encode();
     name = Form("%s+%02d", name.Data(), bits);
     TH1 * h = Identify(name);
     if (!h) { Info("Fill", "%s not found", name.Data()); return 0; }

     Int_t bin = -2;
     Int_t dimension = h->GetDimension();
     Float_t weight = 1;
     if (dimension == 1) { 
	  weight = y;
	  TH1D * hh = (TH1D *)h; 
	  bin = hh->Fill(x, y); 
//	  hh->BufferEmpty();
     } else if (dimension == 2) { 
	  weight = z;
	  TH2D * hh = (TH2D *)h;
	  bin = hh->Fill(x, y, z); 
//	  hh->BufferEmpty();
     } else if (dimension == 3) { 
	  weight = w;
	  TH3D * hh = (TH3D *)h;
	  bin = hh->Fill(x, y, z, w);  
//	  hh->BufferEmpty();
     } else Info("Fill", "Hmm"); 

     if (fSpace) fSpace->FillCorrelationMatrix(w);

     return bin;
}


TList * K3Control::RootList()
{
     if (!fList) return fList;
     TList * rootList = new TList();
     TIter next(fList);
     while (TH1*h = (TH1*)next()) {
	  TString hN = h->GetName();
	  if (!hN.Contains("+")) rootList->Add(h);  
     }

     return rootList;
}


TList * K3Control::StateList(Int_t generation, const char * project, const char * reproject)
{//all hists with same bits enables
     if (!fList) return fList;
     TList * state = new TList();
     TIter next(fList);
     while (TH1 * h = (TH1 *)next()) {
	  state->Add(h);
/*
  not implemented 
*/
     }

     return state;
}


TString K3Control::Glist(TString name, Bool_t nonempty)
{
     if (!fList) return name;
     TIter next(fList);
     Info("Glist", "<%s><%s><%s><%s><%s><%s><%s>", "dimension", "name", "title", "x", "y", "z", "n");
     while (TH1*h = (TH1*)next()) {
	  TString hN = h->GetName();
	  if (!name.CompareTo("*") || hN.Contains(name)) { 
	       Int_t dimension = h->GetDimension();
	       Double_t entries = h->GetEntries();
	       if (nonempty && entries == 0.) continue;
	       TString hT = h->GetTitle();
	       TString hX = h->GetXaxis()->GetTitle();
	       TString hY = h->GetYaxis()->GetTitle();
	       TString hZ = h->GetZaxis()->GetTitle();
	       Info("Glist", "<%d><%s><%s><%s><%s><%s><%f>", dimension, hN.Data(), hT.Data(), hX.Data(), hY.Data(), hZ.Data(), entries);
	  } 
     }
     return name;
}

void K3Control::Multiplex()
{
     if (!fSpace) {
	  Info("Multiplex", "Sorry, empty space.");
	  return; 
     }     

     fSpace->On();
     for (Int_t n = 0; n < fSpace->Encode() + 1; n++) this->Append(Form("%02d", n), fSpace->Decode(n));
     fSpace->Off();

//     this->RemoveRoot();
}

void K3Control::RemoveRoot()
{
     TList * rootlist = this->RootList();
     TIter next(rootlist);
     while (TH1 * h = (TH1 *)next()) delete h;
}



void K3Control::Append(const char * append, const char * title)
{
     TList * rootlist = this->RootList();
     TIter next(rootlist);
     while (TH1 * h = (TH1 *)next()) {
	  TString hname = h->GetName();
	  hname += "+";
	  hname += append;
	  TH1 * hh = (TH1 *)h->Clone(hname);
	  if (title) hh->SetTitle(title);
	  else hh->SetTitle(append);
	  fList->Add(hh);
     }

     delete rootlist;

}



void K3Control::Entry(Int_t entry)
{
     if (entry == 0) {
	  fCount = 0;
	  TDatime*datime = new TDatime();
	  fTime = datime->Get();
	  delete datime;
	  Info("Entry", "first event processed successfuly. Current time = %d", fTime);
     } else if (fNumi == 0) {
	  Warning("Entry", "Please make use of the method SetNumi() to set the number of events");
	  fNumi = 1;
     } else { 	
	  Double_t fraction = Double_t(entry) / Double_t(fNumi);
	  //	Int_t count = Int_t(TMath::Log(1 / fraction));
	  Int_t count = Int_t(fraction * 100);
	  if (count != fCount || fNumi == entry + 1) {
	       TDatime*datime = new TDatime();
	       Int_t timePast = datime->Get() - fTime;
	       delete datime;

	       TString message = Form("%10d / %d, %6.2f", entry, fNumi, fraction * 100);
	       message += " pc";
	       if (timePast == 0) {
		    Error("Entry", "zero timePast");		
	       } else {
		    Double_t speed = (Double_t(entry) + 1) / Double_t(timePast);  
		    if (Int_t(speed) == 0) {
			 Error("Entry", "zero speed");
		    } else {
			 //		    Int_t timeLeft = (fNumi - entry) / Int_t(speed) / 60;
			 //		    message = Form("%s %5d s %3d min %10.0f events/s", message.Data(), timePast, timeLeft, speed);
			 Double_t timeLeft = Double_t(fNumi - entry) / (speed * 60);
			 message = Form("%s %5d s %10.1f min %10.1f events/s", message.Data(), timePast, timeLeft, speed);
		    }
	       }
	       Info("Entry", message);
	       fCount = count;
	  }
	
     }
} 

void K3Control::Panopm() 
{
     Info("Panopm", "%s,%s,%d,%f,%d,%d,%s",
	  fName.Data(), fTitle.Data(),
	  fNumi, fLumi, fMC, fSim, fSteer.Data());
}



TList * K3Control::FamilyList(TString name,
			      const char * project, const char * reproject)
{//all hists with same root
     if (!fList) return fList;
     TList * family = new TList();
     TIter next(fList);
     while (TH1 * h = (TH1 *)next()) {
	  TString hN = h->GetName();
	  if (hN.Contains(name)) 
	       if (h->GetEntries() > 0.)
		    family->Add(h);  
     }

     return family;
}


/*
TList * K3Control::Similar(TString name, TString project, TString reproject)
{
     TList * similar = new TList();
     TIter next(fList);
     while (TH1*h = (TH1*)next()) {
	  TString hname = h->GetName();
	  if (hname.Contains(Form("%s+",name.Data()))) 
	       if (h->GetEntries() > 0.) {
		    hname.ReplaceAll(fName+"_", "");
		    similar->Add(Identify(hname, project, reproject));
	       }
     } 
     return similar;
}

*/
