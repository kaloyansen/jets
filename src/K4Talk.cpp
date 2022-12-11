//____________________________________________________________________
//
// presentation driver
//
// $Id$
// Author: kkrastev <kaloyan@mail.desy.de>
// Update: 2009-11-12 12:45:54+0100
// Copyright: 2009 (C) kkrastev
//
/* Begin_Macro(source)
   {
   // A simple example:
   // This script will produce a presentation with three slides.
   // It will be saved as "moon.pdf".

   gROOT->SetBatch();
   TCanvas*canvas = new TCanvas("Kaloyan Krastev (LPSC)", "Moon meeting(11.VII.2022)");
   K4Talk::Instance("moon.pdf", canvas);
   gTalk->Slide("Welcome to the Moon");
   gTalk->Slide("No food");
   gTalk->Slide("No drink");
   gTalk->Slide("No air!!");
   gTalk->Draw("Let's go to Mars!");
   gTalk->End();
   return canvas;
   }
   End_Macro */

#ifndef ROOT_K4Talk
#include "K4Talk.h"
#endif

K4Talk * gTalk = 0;

ClassImp(K4Talk);

K4Talk * K4Talk::fTalk = 0;


K4Talk::K4Talk(TString pdfname, TCanvas * canvas) : TPDF(pdfname) {
     if (!canvas) {
          exit(0);
     }
     fCanvas = canvas;
     fCanvas->SetFillStyle(0);
}


K4Talk & K4Talk::Instance(TString pdfname, TCanvas * canvas, Int_t color, Int_t font) {
     if (!fTalk) {
	  fTalk = new K4Talk(pdfname, canvas);
	  fTalk->Info("Instance", "New presentation %s created", pdfname.Data());
          fTalk->Ini(color);
          fTalk->Style(0, 0, 0, 0.05, -0.1, font);
     } else {
	  fTalk->Warning("Instance", "Ignored. K4Talk is a singleton class");
     }
     return *fTalk ;
}


void K4Talk::Ini(Int_t color) {
     fColor = color;//kBlack;//kBlue;//880;//kViolet;
     fObject = 0;
     fPad = 0;
     fPage = 0;
     fTop = 8;
     fBottom = 20;
     fTravail = kFALSE;
     fPrint = kFALSE;

     if (!gTalk) {
	  gTalk = this;
	  gROOT->GetListOfSpecials()->Add(gTalk);
     }

}


void K4Talk::End() {
     this->Info("End", "travail = %d", fTravail);
     Close();
     if (fTravail) gSystem->Exec(Form("$HOME/Myxa/mode/tcsh/travail.csh %s", fName.Data()));

     this->Info("End", "Written to %s", GetName());
     if (gTalk == this)	gTalk = 0;
}

void K4Talk::Inverse() 
{
     fInverse = 1;
}


void K4Talk::Slide(const char * title) {
     if (fPrint) PrintSlide(Form("%s.gif", fTitle.Data()));
     this->SetTitle(title);
     TString myName = fCanvas->GetName();
     TString myMeeting = fCanvas->GetTitle();
     fCanvas->Update();

     int col = fColor + 12;
     if (fInverse) col = -1;	  

     if (fPage == 0) {
	  Draw(title,         1,  5, 2, 1, fColor, col);
	  Draw(myName,        1, 10, 6, 1, fColor, col);
	  Draw(myMeeting,     1, 10, 8, 1, fColor, col);
	  fTalkTitle = title;
     } else {
	  fCanvas->Clear();
	  if (title && !fPrint) {
	       TString present = Form("%s, %s", myName.Data(), myMeeting.Data());
	       TString page = Form("page %2.d", fPage);
	       Draw(title,   1,       8,               1,  1, fColor, col, kFALSE);
	       Draw(page,        4, fBottom, 4 * fBottom - 0,      1, fColor, col, kFALSE);
	       Draw(present,     4, fBottom, 4 * fBottom - 1,  1, fColor, col, kFALSE);
	       Draw(fTalkTitle,  4, fBottom, 4 * fBottom - 2,  1, fColor, col, kFALSE);
	  }
     }
     fPage++;
     this->Info("Slide", "%d %s", fPage, title);
}



void K4Talk::Divide(Int_t x, Int_t y, Int_t n, Float_t & x0, Float_t & y0, Float_t & x1, Float_t & y1, Bool_t margin)
{
     Off();
     TCanvas*c = new TCanvas();
     if (margin) c->Divide(x, y);
     else c->Divide(x, y, -1, -1);
     TVirtualPad*pad = c->cd(n);
     x0 = pad->GetXlowNDC();
     y0 = pad->GetYlowNDC();
     x1 = x0+pad->GetWNDC();
     y1 = y0+pad->GetHNDC();
     c->Close();
     delete c;
     On();
}


TH2D * K4Talk::DrawImage(TString name, Int_t x, Int_t y, Int_t n, const char * option)
{
     TH2D * h2d = 0;

     TFile * file = new TFile("images.root");
     if (!file->IsOpen()) {
	  this->Error("DrawImage", "!file->IsOpen()");
	  return h2d;
     }

     h2d = (TH2D*)file->Get(name);
     if (!h2d) {
	  this->Error("DrawImage", "!h2d");
	  return h2d;
     }
     h2d->SetDirectory(0);
     file->Close();
     delete file;

     Float_t x0, y0, x1, y1;
     Divide(x, y, n, x0, y0, x1, y1);
     TString opt = Form("%s,AH,COL", option);
     Draw(h2d, x0, y0, x1, y1, opt);
     return h2d;
}



K4Stack * K4Talk::StackFromList(TList * list)
{
     K4Stack * sta = new K4Stack(list);
     return sta;
}

K3Control * K4Talk::DrawControl(K3Control * control)
{
     if (!control) {
	  this->Info("DrawControl", "!control");
	  return control;
     }

     this->Info("DrawControl", control->GetName());
     this->Slide(control->GetName());
     this->Draw(control->GetSpace()->CorrelationMatrixHistogram(), 1, 1, 1, "col, text");

     TList * rootList = control->RootList();
     TIter next(rootList);
     while (TH1 * h = (TH1 *)next()) {
	  Int_t dim = h->GetDimension();
	  TList * family = control->FamilyList(h->GetName());
	  TIter member(family);
	  this->Slide(Form("%s                  i%d", h->GetTitle(), dim));
	  if (dim == 1) {
	       K4Stack * sta = new K4Stack(family);
	       if (family->GetEntries() > 0) {
		    this->Style(110000, 1);
		    this->Draw(sta, 1, 1, 1, "iso, hist, e, col");
		    this->DrawLegend(2, 3, 2, 3);
	       }
	  } 
	  else if (dim == 2) this->DrawList(family, "col");
	  else if (dim == 3) while (TH1 * h = (TH1 *)member()) {
//	       this->Style(110000, 1);
	       this->Slide(Form("%s                  i%d", h->GetTitle(), dim));
	       this->DrawLayers(h);
//		    this->Draw(h);
	  }
	  else this->Info("DrawControl", Form("dim %d not implemented", dim));
	  
	  delete family;
     }

     delete rootList;
     K3Space * space = control->GetSpace();
     if (space) space->Print();

     return control;
}


TH1 * K4Talk::DrawLayer(Int_t layer, TH1 * h1,Int_t x, Int_t y, Int_t n, const char * option, Bool_t margin)

{
     if (!h1) return h1;

     TH3D * h3 = (TH3D *) h1;
//     TObjArray * array = new TObjArray();
     // for (Int_t bin = 1; bin <= h3->GetNbinsZ(); bin++) {
     // 	  h3->GetZaxis()->SetRange(bin, bin);
     // 	  TH2D * h2 = (TH2D *)h3->Project3D(Form("yx_%d", bin));
     // 	  array->Add(h2);
     // }

     h3->GetZaxis()->SetRange(layer, layer);
     TH2D * h2 = (TH2D *)h3->Project3D(Form("yx_%d", layer));
     TRandom random;
     h2->SetName(Form("%f", random.Gaus()));
//     TH1 * mine = (TH1 *)array->At(layer - 1);
     this->Draw(h2, x, y, n, option, margin);
//     delete array;
//     return h1;
     return h2;
}

TH1 * K4Talk::DrawLayers(TH1 * h1, const char * option)
{
     if (!h1) return h1;

     TH3D * h3 = (TH3D *) h1;
     TObjArray * array = new TObjArray();
//     for (Int_t bin = 1; bin <= h3->GetNbinsZ(); bin++) {
     for (Int_t bin = 1; bin <= 30; bin++) {
	  h3->GetZaxis()->SetRange(bin, bin);
	  TH2D * h2 = (TH2D *)h3->Project3D(Form("yx_%d", bin));
	  array->Add(h2);
     }

     this->DrawTHArray(array, option, kFALSE);
     return h1;
}




void K4Talk::Position(Int_t n, Int_t & x, Int_t & y)
{
     x = (Int_t)TMath::Sqrt(n);
     y = x;
     if (x * y < n) x++;
     if (x * y < n) y++;
}



TObjArray*K4Talk::DrawK4StackArray(TObjArray * array, const char * option) {

     TIterator*iterator = array->MakeIterator();
     if (!array) return 0;
     Int_t x, y, n = array->GetEntriesFast();
     this->Position(n, x, y);
     n = 0;
     while (TObject*object = (TObject*)iterator->Next()) {
	  K4Stack*mama = (K4Stack*)object;
	  mama->NormalizeTo(1);
	  this->Draw(mama, x, y, ++n, option);
     }

     return array;
}

TObjArray * K4Talk::DrawTHArray(TObjArray * array, const char * option, Bool_t margin)
{
     if (!array) return 0;
     TIterator * iterator = array->MakeIterator();
     Int_t x, y, n = array->GetEntriesFast();
     this->Position(n, x, y);
     n = 0;
     while (TObject * object = (TObject *)iterator->Next()) {
	  TH1 * mama = (TH1 *)object;
	  this->Draw(mama, x, y, ++n, option, margin);
     }

     return array;
}

TList * K4Talk::DrawList(TList * array, const char * option, Bool_t margin)
{//draw hists on one slide
//     this->Style(110000, 1);
     if (!array) return 0;
     TIterator * iterator = array->MakeIterator();
     Int_t x, y, n = array->GetEntries();
     this->Position(n, x, y);
     n = 0;
     while (TObject * object = (TObject *)iterator->Next()) {
	  TH1 * mama = (TH1 *)object;
	  this->Draw(mama, x, y, ++n, option, margin);
	  this->DrawLegend();
     }

     return array;
/*
     Int_t n = array->GetEntries();
     Int_t m = 0;
     while (m < n) {
	  TH1*mama = (TH1*)array->At(m);
	  this->Slide(mama->GetName());
	  this->Draw(mama, 1, 1, 1, option);
	  m++;
     }

     return array;
*/
}

void K4Talk::DrawObjectFromFile(TString name, TString filename,	Int_t x, Int_t y, Int_t n, const char * option, Bool_t margin)
{
     TObject * obj = 0;
     TFile * file = TFile::Open(filename);
     if (file->IsZombie()) { Error("DrawObjectFromFile", "!file"); return; }
     TObject * oobj = (TObject *)file->Get(name);
     if (!oobj) { Error("DrawObjectFromFile", "!oobj"); return; }
     obj = (TObject *)oobj->Clone(name + "_clone");
     if (!obj) { Error("DrawObjectFromFile", "!obj"); return; }
     obj->Print();
     this->Draw(obj, x, y, n, option, margin);
//     file.Close();
}



TObject * K4Talk::Draw(TObject * object, Int_t x, Int_t y, Int_t n, const char * option, Bool_t margin)
{
     Float_t x0, y0, x1, y1;
     Divide(x, y, n, x0, y0, x1, y1, margin);
     Draw(object, x0, y0, x1, y1, option, margin);
     return object;
}


void K4Talk::Draw(TObject * object, Float_t x0, Float_t y0, Float_t x1, Float_t y1, const char * option, Bool_t margin)
{//private
     if (!object) {	this->Error("Draw", "!object");	return;    }
     if (fTitle.CompareTo("")) {	Shrink(y0);	Shrink(y1);    }

     fCanvas->cd();
     fPad = new TPad("a", "b", x0, y0, x1, y1);

//     fPad->SetFillColor(kWhite);
//     fPad->SetFillStyle(0);
     fPad->Draw();
     if (!margin) {
	  fPad->SetTopMargin(0);
	  fPad->SetRightMargin(0);
	  fPad->SetBottomMargin(0);
	  fPad->SetLeftMargin(0);
     }

     fPad->cd();

//     object->UseCurrentStyle();
//     this->Logy();
     object->Draw(option);

     fObject = object;
}




TLine * K4Talk::DrawLine(Float_t x0, Float_t y0, Float_t x1, Float_t y1, Int_t color) {
     TLine * line = new TLine();
     fPad->cd();
     if (color < 0) line->SetLineColor(fColor);
     else line->SetLineColor(color);
     line->SetLineStyle(2);
     line->SetLineWidth(2);
     line->DrawLine(x0,y0,x1,y1);
     fCanvas->cd();
     return line;
}





void K4Talk::Draw(TString what, Int_t x, Int_t y, Int_t n, Float_t size, Int_t color, Int_t fillcolor, Bool_t shrink) {
     Float_t x0, y0, x1, y1;
     Divide(x, y, n, x0, y0, x1, y1);
     if (shrink && fTitle.CompareTo("")) {
	  Shrink(y0);
	  Shrink(y1);
     }

     if (what.Contains(";")) {
	  Off();
	  K4Stack*del = new K4Stack();
	  Int_t max = del->CountStrings(what,";");
	  TCanvas*canvas = new TCanvas(what,what);
	  canvas->Divide(1, max);
	  for (Int_t i = 0; i < max; ++i) {
	       TVirtualPad*vip = canvas->cd(i + 1);
	       Float_t y0new = vip->GetYlowNDC();
	       Float_t y1new = y0new + vip->GetHNDC();
	       TString sub = del->TakeString(what, i, ";");
	       On();
	       fCanvas->cd();
	       DrawText(sub, //0,0,1,1,
			x0, y0 + (y1 - y0) * y0new,
			x1, y0 + (y1 - y0) * y1new,
			size, color, fillcolor);
	       Off();
	  }
	  delete canvas;
	  delete del;
	  On();
	  return;
     }


     DrawText(what, x0, y0, x1, y1, size, color, fillcolor);
}



void K4Talk::DrawText(TString what, Float_t x0, Float_t y0, Float_t x1, Float_t y1, Float_t size, Int_t color, Int_t fillcolor) {
     TPaveText * pt = new TPaveText(x0, y0, x1, y1);
     TText*text = pt->AddText(what);
     if (color < 0) text->SetTextColor(fColor);
     else text->SetTextColor(color);
     if (fillcolor < 0) pt->SetFillStyle(0);
     else {
	  pt->SetFillColor(fillcolor);
	  pt->SetFillStyle(1001);
     }
     pt->SetBorderSize(0);
     //    pt->SetTextAlign(13);
//     pt->SetTextAlign(12);
     pt->SetTextAlign(32);

     Float_t new_size = pt->GetTextSize();
     new_size *= size;
     //    text->SetTextSize(size);
     pt->SetTextSize(new_size);
     if (what.Contains(".slide")) {
	  char * path = gSystem->ExpandPathName(what.Data());
	  if (gSystem->AccessPathName(path)) {
	       this->Error("DrawText", Form("Cannot access %s", path));
	  } else {
	       this->Info("DrawText", Form("Import %s", path));
	       pt->SetTextFont(82); 
	       pt->SetTextFont(102); 
	       pt->DrawFile(path);
	  }
     } else  pt->Draw();

}


TLegend * K4Talk::DrawLegend(Int_t x, Int_t y, Int_t n, Float_t size)
{
     fPad->cd();
     Float_t cursize = 1;
     TLegend * legend = 0;
     if (fObject == 0) return legend;
     if (fObject->InheritsFrom("K4Stack")) {
	  K4Stack * sta = (K4Stack *)fObject;
	  cursize = sta->GetSize();
	  TString title;
	  legend = new TLegend(0, 0, 1, 1, "", "");
	  legend->SetBorderSize(0);
	  TIter next(sta->fHist);
	  while (TH1 * h = (TH1 *)next()) {
	       if (!h) continue;
	       title = h->GetTitle();
//	       title = h->GetName();
	       if (h->GetFillColor() != 0 || h->GetFillStyle() != 1001) legend->AddEntry(h, title, "F");
	       else if (h->GetMarkerStyle() != 1) legend->AddEntry(h, title, "PE1");
	       else legend->AddEntry(h, title, "LE");

	  }
     } else if (fObject->InheritsFrom("TMultiGraph")) {
	  TMultiGraph * graph = (TMultiGraph *)fObject;
	  cursize = graph->GetXaxis()->GetTitleSize();
	  legend = new TLegend(0, 0, 1, 1, "", "");
	  legend->SetBorderSize(0);
	  TIter next(graph->GetListOfGraphs());
	  TObject * o = 0;
	  while ((o = next())) legend->AddEntry(o, o->GetTitle(), "p,l");
     } else {
	  this->Warning("DrawLegend","not implemented");
//	  fObject->Print();
     }

     if (legend) {
	  this->Draw(legend, x, y ,n);
	  //	legend->SetTextSize(0.19*size);
//	  legend->SetFillColor(kWhite);
	  legend->SetTextSize(cursize * size);
     }

     //    fCanvas->cd();
     return legend;
}



TObject*K4Talk::Last() { return fObject;}
void K4Talk::SetTravail() { fTravail = kTRUE; }
void K4Talk::Shrink(Float_t & y) { y = y * (1 - 1 / Float_t(fTop) - 1 / Float_t(fBottom)) + 1 / Float_t(fBottom); }
void K4Talk::PrintSlide(const char *filename) const { fCanvas->Print(Form("gif/%s", filename), "gif"); }
void K4Talk::Logx() { fPad->SetLogx(); }
void K4Talk::Logy() { fPad->SetLogy(); }





TStyle * K4Talk::Style(Int_t stat, Int_t title, Int_t border, Float_t margin, Float_t standard, Int_t font) {

     TStyle * s = new TStyle("Plain", "Plain");//?
     Float_t size = 0.04;


     s->SetCanvasColor(-1);
     s->SetCanvasBorderMode(0);
     s->SetCanvasBorderSize(border);

     s->SetFillColor(-1);
     s->SetFillStyle(4000);

//     s->SetHistFillColor(-1);

     s->SetFrameBorderMode(0);
     s->SetFrameBorderSize(0);
     s->SetFrameFillColor(-1);

     s->SetLabelFont(font,"xyz");
     s->SetLabelSize(size, "xyz");

     s->SetLegendBorderSize(border);

     s->SetOptDate(11);
     s->SetOptFit(1);

     s->SetPadBorderMode(0);
     s->SetPadBottomMargin(standard);
     s->SetPadColor(-1);
     s->SetPadLeftMargin(standard);
     s->SetPadRightMargin(margin);
//     s->SetPadTickX(1);
//     s->SetPadTickY(1);
     s->SetPadTopMargin(margin);

     s->SetPalette(1);

     s->SetStatBorderSize(border);
     s->SetStatFont(font);
     s->SetStatFontSize(size);
     s->SetStatStyle(0);
     s->SetStatTextColor(kBlack);
     s->SetStatY(1 - margin);
     s->SetStatX(1 - margin);
     s->SetOptStat(stat);

     s->SetTextFont(font);
     s->SetTextSizePixels(21);

     s->SetTitleBorderSize(border);
     s->SetTitleFillColor(-1);
     s->SetTitleFont(font,"xyz");
     s->SetTitleH(0);
     s->SetTitleOffset(1.2,"y");//for big statistics y-title overlaps with y-axis numbers
     s->SetTitleSize(size);
     s->SetTitleX(standard);
     s->SetTitleY(1 - margin);
     s->SetTitleSize(size, "xyz");
     s->SetTitleStyle(0);
     s->SetOptTitle(title);


     s->cd();






     return s;
}



//____________________________________________________________________
//
// EOF
//

