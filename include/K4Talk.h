// -*- mode: c++ -*-
//____________________________________________________________________
//
// $Id$
// Author: kkrastev <kaloyan@mail.desy.de>
// Update: 2009-11-12 12:39:26+0100
// Copyright: 2009 (C) kkrastev
//
#ifndef ROOT_K4Talk
#define ROOT_K4Talk
#ifndef ROOT_TPDF
#include "TPDF.h"
#endif
#include "TCanvas.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH2D.h"
#include "TH3D.h"
#include "THStack.h"
#include "TGaxis.h"
#include "TImage.h"
#include "TMultiGraph.h"
#include "TPaveText.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TSystem.h"
#include "K3Control.h"
#include "K4Stack.h"

class K4Talk : public TPDF
{
private:
     K4Talk(TString, TCanvas * canvas = 0);

     void               Ini(Int_t color);
     void               Shrink(Float_t&);


     void               Divide(Int_t, Int_t, Int_t, Float_t &, Float_t &, Float_t &, Float_t &, Bool_t margin = kTRUE);
     void               Draw(TObject *, Float_t, Float_t, Float_t, Float_t, const char * option = 0, Bool_t margin = kTRUE);
     void               DrawText(TString, Float_t, Float_t, Float_t, Float_t, Float_t size = 1, Int_t color = -1, Int_t fillcolor = -1);

     Bool_t             fPrint;
     Bool_t             fInverse;
     Bool_t             fTravail;
     Int_t              fPage;
     Int_t              fColor;
     Int_t              fTop;
     Int_t              fBottom;
     TString            fTalkTitle;
     TObject          * fObject;     // A pointer to the last drawn object
     TPad             * fPad;        // A pointer to the current pad
     TCanvas          * fCanvas;     // A pointer to the current slide

protected:
     static K4Talk    * fTalk;  //!

public:
     static K4Talk    & Instance(TString pdfname, TCanvas * canvas = 0, Int_t color = kBlack, Int_t font = 42);

     void               SetPrint() { fPrint = kTRUE; }
     void               Inverse();
     void               End();
     void               Slide(const char * title = 0);
     void               Logy();
     void               Logx();
     void               SetTravail();
     void               PrintSlide(const char* filename = "") const;
     void               Draw(TString, Int_t x = 1,Int_t y = 1,Int_t n = 1, Float_t size = 1,Int_t color = -1,Int_t fillcolor = -1, Bool_t shrink = kTRUE);
     void               DrawObjectFromFile(TString name, TString filename, Int_t x = 1, Int_t y = 1, Int_t n = 1, const char * option = 0, Bool_t margin = kTRUE);
     TH1              * DrawLayer(Int_t layer, TH1 *, Int_t x = 1, Int_t y = 1, Int_t n = 1, const char * option = 0, Bool_t margin = kTRUE);
     TObject          * Draw(TObject *, Int_t x = 1, Int_t y = 1, Int_t n = 1, const char * option = 0, Bool_t margin = kTRUE);
     TObject          * Last();
     TPad             * GetPad() { return fPad; }
     TObjArray        * DrawK4StackArray(TObjArray*, const char * option = 0);
     TObjArray        * DrawTHArray(TObjArray *, const char * option = 0, Bool_t margin = kTRUE);
     TList            * DrawList(TList *, const char * option = 0, Bool_t margin = kTRUE);
     TLine            * DrawLine(Float_t, Float_t, Float_t, Float_t, Int_t color = -1);
     TLegend          * DrawLegend(Int_t x = 3, Int_t y = 3, Int_t n = 3, Float_t size = 1);
     TH2D             * DrawImage(TString, Int_t x = 1, Int_t y = 1, Int_t n = 1, const char * option = 0);
     K4Stack          * StackFromList(TList * list);
     TH1              * DrawLayers(TH1 *, const char * option = "col");
     K3Control        * DrawControl(K3Control * control = 0);

     static void        Position(Int_t n, Int_t & x, Int_t & y);
     static TStyle    * Style(Int_t stat = 0, Int_t title = 0, Int_t border = 0, Float_t margin = 0.05, Float_t standard = 0.1, Int_t font = 42);

     ClassDef(K4Talk,0) //presentation driver
};

R__EXTERN K4Talk * gTalk;

#endif
