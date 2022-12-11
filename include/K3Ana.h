#ifndef __K3Ana__
#define __K3Ana__
#include "TClass.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TKey.h"
#include "TRandom.h"
#include "K3Control.h"
#include "K4Stack.h"
using namespace std;

class K3Ana: public K3Control {
private:
     Int_t        fN;

public:
     K3Ana();
     ~K3Ana();

     void         GetFile(TString, Int_t max = 0);
     void         GetControl(K3Control * control);
     Int_t        fI;
     TString      fCname[100];
     K3Control    fC[100];

     void         Control(TString name, K3Control&control);
     static TF1 * Resolution(TMultiGraph*m, TString option = "");
     static TF1 * Resolution(TH1*, Float_t, Float_t);
     static void  PrintFitGausParameters(TF1 * fitfctn);

     Bool_t       Loop(Int_t n = -1);
     Int_t        GetN() { return fN; }
     TH1        * Sum(TString name, TString project = "", TString reproject = "", Int_t norm = 0);
     K4Stack    * All(TString name, TString project = "", TString reproject = "", Int_t norm = 0);
     //    TGraphErrors*Resolution(TString mode, Bool_t space = kTRUE, K4Stack*fits = 0, TString title = 0);
     TGraphErrors*Resolution(TString mode, Bool_t space = kTRUE, TClonesArray*stax = 0, TString title = "");

     //    TFile*File() { return f;}
     //    K3Control*First();
     //    K3Space*GetSpace(Int_t i) { return fC[i].GetSpace(); }
     /*
       void Norm(TProfile*,TString);
       void Norm(TH1*,TString);
       void Norm(TH1*,Float_t);
       Float_t Norm(TH1*,TH1*);
       Float_t Lumi(TH1*);

       TH1F*HistStay(TString var,TString mc);
       TH1F*HistBias(TString var,TString mc);
       TF1*FitBias(TString var,TString mc,Float_t&min,Float_t&max);

       TH1F*GetHi(TString variable="Yh",TString sample="do6",TString level="",Float_t scale=1,Float_t r=1);
       TH2F*GetHi2(TString variable="Yh",TString sample="do6",TString level="",Float_t scale=1);
       TH3F*GetHi3(TString variable="Yh",TString sample="do6",TString level="",Float_t scale=1);
       //    TProfile*GetProfile(TString variable="Yh",TString sample="do6",TString level="",Float_t scale=1);
       TH1F*HistPlus(TString var,TString l1,TString l2,TString name,TString title,TString level="",Float_t sc=1,Float_t r=1);
       TH2F*Hist2Plus(TString var,TString l1,TString l2,TString name,TString title,TString level="",Float_t sc=1,Float_t r=1);
       TH3F*Hist3Plus(TString var,TString l1,TString l2,TString name,TString title,TString level="",Float_t sc=1,Float_t r=1);
       //    TProfile*ProfilePlus(TString var,TString layer1,TString layer2,TString name,TString title,TString level="",Float_t scale=1);
       TH1F*HistMCPlus(TString var,TString name,TString mc,Float_t sc=1,Float_t r=1,TString option="");
       TH1F*HistCorrectedData(TString layer,TString var,TString mc,Float_t sc=1,Float_t r=1,TString option="",Bool_t bias=kFALSE);
       TH1F*HistSimulatedMC(TString layer,TString var,TString mc,Float_t sc=1,Float_t r=1,TString option="");
       TH1F*HistCorrectedError(TString layer,TString var,TString mc,Float_t sc=1,Float_t r=1,TString option="+",Bool_t bias=kFALSE);
       TGraphAsymmErrors*GraphEff(TString layer,TString var,TString trigger,TString monitor);
       TH1F*Systematics(TH1F*,TH1F*);//a histogram with the ratio from systematic shift
     */

     ClassDef(K3Ana,1) // Class for analysis layout
};
#endif
