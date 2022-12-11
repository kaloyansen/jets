
/*************************************************************************
 * Author: Kaloyan Kratsev <mailto:krastev@lpsc.in2p3.fr>                *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/


#ifndef __K3Control__
#define __K3Control__

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// K3Control                                                            //
//                                                                      //
// Histogram storage class.                                             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TDatime.h"
#include "TH2.h"
#include "TH3.h"
#include "TGraphErrors.h"
#include "TList.h"
#include "TMultiGraph.h"
#include "TPaveStats.h"
#include "TProfile3D.h"
#include "TProfile2D.h"

#include "K3Space.h"

class K3Control: public TNamed {
private:
     Bool_t	 fSim;
     Int_t	 fNumi;
     Int_t	 fCount;//!
     Int_t	 fTime;//!
     Int_t	 fMC;
     Float_t	 fLumi;
     TString	 fSteer;

     void	 Ini();
     void        RemoveRoot();
     void	 Remember(const char * xTitle, const char * yTitle, const char * zTitle);

public:

     K3Control();
     K3Control(TString, TString);
     ~K3Control();

     TH1       * fLast; 
     TList     * fList;
     K3Space   * fSpace;

     TList     * GetList() { return fList;}
     TList     * RootList();
     TList     * FamilyList(TString name,
     			    const char * project = 0, const char * reproject = 0);
     TList     * StateList(Int_t generation,
     			   const char * project = 0, const char * reproject = 0);

     void	 SetAll(Int_t numi = 0, Float_t lumi = 0, Int_t ismc = -1,
		        Bool_t issim = kFALSE, const char * steer = 0);
     void        SetNumi(Int_t numi = 0) { fNumi = numi; }
     void 	 SetLumi(Float_t lumi) {fLumi=lumi;}
     void 	 Draw(Option_t * option = "");
     void 	 Panopm();
     void	 Entry(Int_t entry);
     void        Multiplex();
     void	 Append(const char * append = 0, const char * title = 0);

     Bool_t	 IsSim() {return fSim;}

     Int_t       IsMC() {return fMC;}
     Int_t	 GetNumi() {return fNumi;}
     Int_t	 GetNumberOfHistograms() { return fList->GetEntries(); }
     Int_t	 Fill(TString name, Double_t x, Double_t y = 1, Double_t z = 1, Double_t w = 1);

     Float_t	 GetLumi() {return fLumi;}
     Float_t	 GetSigma() {return (Float_t)fNumi/fLumi;}

     TString	 GetSteer() {return fSteer;}
     TString	 Glist(TString name = "*", Bool_t nonempty = kFALSE);

     TH1       * Identify(TString name, const char * project = 0, const char * reproject = 0);
     void        Freeze(bool frozen = 1);
     void        Book(Int_t dimension,
		      const char * name, const char * title, const char * xTitle, const char * yTitle, const char * zTitle,
		      Int_t nbinsx, Double_t xlow, Double_t xup,
		      Int_t nbinsy = 3, Double_t ylow = -1, Double_t yup = 1,
		      Int_t nbinsz = 3, Double_t zlow = -1, Double_t zup = 1);
// abandoned
//      TH1*	 BookArray(Int_t      dimension,//array
// 			   const char*name,       const char    *title,
// 			   const char*xTitle,     const char    *yTitle,    const char*zTitle,
// 			   Int_t      nbinsx,     const Double_t*xbins,
// 			   Int_t      nbinsy = 3, const Double_t*ybins = 0,
// 			   Int_t      nbinsz = 3, const Double_t*zbins = 0);     

//     TList    *	Similar(TString name, TString project = 0, TString reproject = 0);

     K3Space  *	Space() { fSpace = new K3Space(); return fSpace; }
     K3Space  *	GetSpace() { return fSpace; }

     ClassDef(K3Control, 7); // Base class for storing results during data processing
};

#endif
