#ifndef __K4Stack__
#define __K4Stack__
#include <iostream>
#include "TCanvas.h"
#include "TClonesArray.h"
#include "TGaxis.h"
#include "TH1.h"
#include "TF1.h"
#include "TLegend.h"
#include "TLine.h"
#include "TList.h"
#include "TMath.h"
#include "TObjString.h"
#include "TRandom.h"
//#include "TROOT.h"
#include "TStyle.h"

using namespace std;

class K4Stack : public TNamed {

     TString          sNorm, sNewX;

public:

     Int_t            iLogy, iLogx, iLines, fDetect;

     TList          * fHist;
     TLegend        * fLegend;   //! Stack legend
     TClonesArray   * fLineClonesArray;  //! lines

     K4Stack();
     K4Stack(TList * array);
     K4Stack(TString name, TString title = "", TString norm = "no", TString newx = "no");
     virtual         ~K4Stack();

     void             Ini();
     void             Detect();
     void             SetMinimum(Double_t min = 0);
     void             SetMaximum(Double_t max = 0);
     void             List(TString option = "");
     void             Renorm(TString);
     void             Locate(TString, Float_t &, Float_t &, Float_t &, Float_t &, Int_t & margin, Bool_t debug = kFALSE);
     void             Line(TString opt = "hor", Float_t k = 1, Int_t width = 2,Int_t style = 2,Int_t color = 1); 
     void             Add(TList * array);
     void             Add(K4Stack *, Float_t k = 1);
     void             Add(TH1 *, Float_t);
     TH1            * Add(TH1 *);
     void             Draw(Option_t * option = "P,E1");

     void             Norm(TString);
     void             Scale(Float_t);
     void             Logy(Int_t);
     void             Logx(Int_t);
     void             AxisTitles(TString &,TString &);
     void             DeleteHistograms();
     void             Normalize() { this->NormalizeTo(1); this->NormalizeToBinWidth(); }
     void             NormalizeTo(Float_t n = 1);
     void             NormalizeToBinWidth();
     void             HistToData(TH1 *,TString);
     //    void           Fit(TString function="gaus", Double_t min = -100, Double_t max = 100);
     void             Fit(TF1 * f, TString option);


     TH1            * Provide(TString option="data");
     Float_t          GetSize();

     //legend
     void             DrawLegend(TString location);
     void             DrawLegend(Float_t x0 = 0.7, Float_t y0 = 0.55,Float_t x1 = 1, Float_t y1 = 0.9);
     inline TLegend * GetLegend() { 	 this->CreateLegend();	 return fLegend;     }
     void             CreateLegend(Float_t x0 = 0, Float_t y0 = 0, Float_t x1 = 1, Float_t y1 = 1);


     Int_t            GetEntries();
     TString          GetNorm() const { return sNorm; }
     TList          * GetHists() const { return fHist; }
     TStyle         * Beauty(Float_t labelSize = 1, Int_t titleLocation = 0, Int_t optStat = 1, TString styleName = "Plain", Int_t color = kBlack); 
     static Int_t     CountStrings(TString big, const TString delim = ","); 
     static TString   TakeString(TString big, Int_t at, const TString delim = ",");

     ClassDef(K4Stack,1); // Base class to extend histogram stack
};
#endif

