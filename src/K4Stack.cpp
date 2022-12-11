#include "K4Stack.h"

ClassImp(K4Stack);

K4Stack::K4Stack() : TNamed("name","title")
{
     this->Ini();
}

K4Stack::K4Stack(TList*array) : TNamed("name","title")
{
     this->Ini();
     this->Add(array);
}

K4Stack::~K4Stack()
{
     if (fLegend) delete fLegend;
     if (fLineClonesArray) {
	  fLineClonesArray->Delete();
	  delete fLineClonesArray;
     }
}

void K4Stack::Ini()
{
     fLegend = 0;
     fLineClonesArray = 0;
     fHist = 0;
     fDetect = -1;
}

void K4Stack::Renorm(TString norm)
{
     sNorm = norm;
}

K4Stack::K4Stack(TString name, TString title, TString norm, TString newx) : TNamed(name.Data(), title.Data())
{
     Ini();
     sNewX=newx;
     sNorm=norm;
     iLines=0;
     iLogy=0;
     iLogx=0;
}


void K4Stack::Add(TList * array)
{
     for (Int_t i = 0; i < array->GetSize(); ++i) {
	  TH1 * h = (TH1 *)array->At(i);
	  if (h->GetEntries() > 0.) h->Print();
	  this->Add(h);
     }
}

void K4Stack::Add(K4Stack * s,Float_t k)
{
     TList * list = s->GetHists();
     for (Int_t i = 0; i < list->GetSize(); ++i) {
	  TH1F * h = (TH1F* )list->At(i);
	  h->Scale(k);
	  this->Add(h);
     }
}



void K4Stack::Add(TH1 * h, Float_t k)
{
     if (!h) return;
     h->Scale(k);
     Add(h);

}

TH1 * K4Stack::Add(TH1 * h)
{
     if (!h) return 0;
     if (!fHist) fHist = new TList();
     fHist->Add(h);
     return h;
}


void K4Stack::Line(TString opt,Float_t k,Int_t width,Int_t style,Int_t color)
{
     if (!fLineClonesArray) fLineClonesArray=new TClonesArray("TLine",0);

     Float_t x1=0.0;
     Float_t y1=0.0;
     Float_t x2=0.0;
     Float_t y2=0.0;

     this->Draw("nostack");
     TH1*z = (TH1*)fHist->At(fDetect);

     if (!opt.CompareTo("hor")) {
	  TAxis*axis=z->GetXaxis();
	  x1=axis->GetXmin();
	  x2=axis->GetXmax();
	  y1=k;
	  y2=k;
     } else if (!opt.CompareTo("ver")) {
	  TAxis*axis=z->GetYaxis();
	  x1=k;
	  x2=k;
	  y1=axis->GetXmin();
	  y2=axis->GetXmax();
     } else {
	  Error("Line","Unforseen option %s",opt.Data());
     }


     TClonesArray&lines=*fLineClonesArray;
     TLine*line=new(lines[iLines++])TLine(x1,y1,x2,y2);
     line->SetLineWidth(width);
     line->SetLineStyle(style);
     line->SetLineColor(color);

}


void K4Stack::DrawLegend(TString location)
{
     Int_t margin;
     Float_t x0,y0,x1,y1;
     Locate(location,x0,y0,x1,y1,margin);
     DrawLegend(x0,y0,x1,y1);

}

void K4Stack::DrawLegend(Float_t x0,Float_t y0,Float_t x1,Float_t y1)
{
     CreateLegend(x0,y0,x1,y1);
     fLegend->Draw("ndc");
}



void K4Stack::List(TString option)
{
     TIter next(fHist);
     TString title;
     Info("List", "stack name=%s,title=%s", this->GetName(), this->GetTitle());
     while (TH1*h=(TH1*)next()) {
	  const char*title=h->GetTitle();
	  const char*name=h->GetName();
	  const char*x=h->GetXaxis()->GetTitle();
	  const char*y=h->GetYaxis()->GetTitle();
	  const char*z=h->GetZaxis()->GetTitle();
	  Info("List", "<%s><%s><%s><%s><%s>", name, title, x, y, z);
	  h->Print(option);
     }
}

Float_t K4Stack::GetSize()
{
     TIter next(fHist);
     while (TH1*h=(TH1*)next()) {
	  TAxis*x = h->GetXaxis();
	  return x->GetTitleSize();
     }
     return 1;
}

TH1 * K4Stack::Provide(TString option)
{
     TH1 * jaba = 0;
     if (!fHist) {
	  Error("Provide", "!fHist");
	  return jaba;
     }
     this->Detect();

     jaba = (TH1 *)fHist->At(fDetect);
     if (!jaba) {
	  Error("Provide", "!jaba");
	  return jaba;
     }
 
     return jaba;

/*
     TH1F * jaba = 0;
     TString sample, name, title;
     TIter next(fHist);
     while (TH1 * h = (TH1 *)next()) {
	  sample = h->GetZaxis()->GetTitle();
	  title = h->GetTitle();
	  name = h->GetName();
	  TH1F * hf = (TH1F *)h;
	  if (!option.CompareTo("data")) {
	       if (sample.Contains("do6") && title.Contains("data"))
		    return hf;
	  } else if (!option.CompareTo("+")) {
	       if (name.Contains("+"))
		    return hf;
	  } else if (!option.CompareTo("-")) {
	       if (name.Contains("-"))
		    return hf;
	  }
     }
     return jaba;
*/
}


void K4Stack::CreateLegend(Float_t x0,Float_t y0,Float_t x1,Float_t y1)
{
     if (fLegend==0) {
	  fLegend=new TLegend(x0,y0,x1,y1, "", "");
     } else {
	  fLegend->Clear();
     }

     fLegend->SetFillStyle(0);
     fLegend->SetBorderSize(0);
     fLegend->SetFillColor(0);
     //    fLegend->SetTextSize(0.07);
     // Add legend items
     TIter next(fHist);
     TString title;
     while (TH1*h=(TH1*)next()) {
	  title=h->GetTitle();
	  if (title.Contains("err")) continue;
	  if (title.Contains("unc")) continue;

	  if (h->GetFillColor()!=0||h->GetFillStyle()!=1001) {
	       fLegend->AddEntry(h,h->GetTitle(),"F");
	  } else if (h->GetMarkerStyle()!=1) {
	       fLegend->AddEntry(h,h->GetTitle(),"PE1");
	  } else {
	       fLegend->AddEntry(h,h->GetTitle(),"LE");
	  }
     }
}

void K4Stack::NormalizeTo(Float_t n)
{
     TIter next(fHist);
     while (TH1*h = (TH1*)next()) {
	  //	TH1*h = (TH1*)hh->Clone();
	  if (h->GetSumw2N()==0) h->Sumw2();
	  h->Scale(n/h->Integral());
	  //	fHist->Add(h);
	  //	fHist->Remove(hh);
     }
     sNorm += "one";
}

void K4Stack::NormalizeToBinWidth()
{
     TIter next(fHist);
     while (TH1 * h = (TH1 *)next()) {
	  if (h->GetSumw2N() == 0) h->Sumw2();
	  for (Int_t bin = 1; bin <= h->GetNbinsX(); ++bin) {
	       Float_t x = h->GetBinContent(bin);
	       Float_t e = h->GetBinError(bin);
	       Float_t w = h->GetBinWidth(bin);
	       h->SetBinContent(bin, x / w);
	       h->SetBinError(bin, e / w);
	  }
     }
     sNorm += "bin";
}



void K4Stack::Scale(Float_t s)
{
     TIter next(fHist);
     while (TH1*h=(TH1*)next()) {
	  h->Scale(s);
     }
}


void K4Stack::Norm(TString norm) { sNorm=norm; }
void K4Stack::Logy(Int_t i) { iLogy=i; }
void K4Stack::Logx(Int_t i) { iLogx=i; }
void K4Stack::AxisTitles(TString & x, TString & y)
{
     if (fHist==0) {
	  Error("AxisTitles","%s empty! Have to return...",this->GetName());
	  return;
     }

     this->Detect();
     TH1 * w = (TH1 *)fHist->At(fDetect);
     TString oldx, vari, unit, in, out, sec;
     
     oldx = w->GetXaxis()->GetTitle();
     vari = this->TakeString(oldx, 0, ",");
     unit = this->TakeString(oldx, 1, ",");

//     vari = w->GetXaxis()->GetTitle();
//     unit = w->GetYaxis()->GetTitle();
     x = vari;
     if (sNewX.CompareTo("no"))
	  x=sNewX;
     in=" (";
     out=")";
     in=" [";
     out="]";
     if (unit.CompareTo("")) {//add units to x axis title
	  x += in;
	  x += unit;
	  x += out;
     }

     y = sNorm;
     
     if (!sNorm.CompareTo("no")) y="Events";
     else if (!sNorm.CompareTo("first")) y="Data events";
     else if (!sNorm.CompareTo("one")) y="1/N";
     else if (!sNorm.CompareTo("lumi")) y="N/L [pb]";
     else if (!sNorm.CompareTo("syst")) y="Uncertainty [%]";
     else if (sNorm.Contains("bin")) {
	  y = "1/N dN/d";
	  y = y + vari;
	  if (unit.CompareTo("")) {
	       y += in;
	       y += unit;
	       y += "^{-1}";
	       y += out;
	  }
     } else if (!sNorm.CompareTo("diff")) {
	  sec="pb";
	  /*
	    if (w->GetMaximum()>100.) {
	    Scale(0.001);
	    sec="nb";
	    } else if (w->GetMaximum()<0.01) {
	    Scale(1000);
	    sec="fb";
	    }
	  */
	  y="d#sigma/d";
	  y+=vari;
	  y+=in;
	  if (unit.CompareTo("")) {
	       y+=sec+"/";
	       y+=unit;
	  } else {
	       y+=sec;
	  }
	  y+=out;
     } else if (!sNorm.CompareTo("sigma")) {
	  sec="pb";
	  y="#frac{1}{#sigma} #frac{d#sigma}{d";
	  y+=vari;
	  y+="}";
	  if (unit.CompareTo("")) {
	       y+=", #frac{1}{";
	       y+=unit;
	       y+="}";
	       //	    y+="^{-1}";
	  }
     } else if (!sNorm.CompareTo("data/mc")) {
	  Line("hor",1.05,1,1,kRed);
	  Line("hor",0.95,1,1,kRed);
	  Line("hor",1.02,1,1,kGreen);
	  Line("hor",0.98,1,1,kGreen);
	  //	SetMinimum(0.8);
	  //	SetMaximum(1.2);
     } else if (!sNorm.CompareTo("ratio to data")) {
	  //	Line("hor",1,1,3,kBlack);
	  //	SetMinimum(0.1);
	  //	SetMaximum(4);
     } else if (!sNorm.CompareTo("efficiency")) {
	  Line("hor",1,1,3,kBlack);
     } else if (!sNorm.CompareTo("C,P,S")) {
	  //	Line("hor",1,1,3,kBlack);
	  //	Line("hor",0.3,1,2,kBlack);
	  //	SetMaximum(2);
	  y="";
     } else {;}
     //else y=sNorm;



}



void K4Stack::HistToData(TH1*h,TString x)
{
     ;    //    Error("HistToData","%s\t%f\t%s",h->GetName(),h->Integral("width"),x.Data());
}




void K4Stack::DeleteHistograms()
{
     TIter next(fHist);
     while (TH1*h=(TH1*)next()) delete h;
}



void K4Stack::Detect()
{
     fDetect = -1;
     if (!fHist) return;

     Float_t hmax, maximum = 1e-6;

     for (Int_t i = 0; i < this->GetEntries(); ++i) {
	  TH1*h = (TH1*)fHist->At(i);
	  if (!h) continue;
	  hmax = h->GetMaximum();
	  fDetect = (hmax > maximum) ? i : fDetect;
	  maximum = (hmax > maximum) ? hmax : maximum;
     }
}

void K4Stack::Draw(Option_t*option)
{
     //    option+="nostack";
     
     TString x, y;
     AxisTitles(x, y);

     TH1 * jaba = this->Provide();
     TAxis * axx = jaba->GetXaxis();
     TAxis * axy = jaba->GetYaxis();
     if (axx) axx->SetTitle(x);
     if (axy) axy->SetTitle(y);


     Int_t color=2;
     //    option+="Hist,E1";

     /*
       if (fHistogram) {
       fHistogram->UseCurrentStyle();
       fHistogram->Draw("axis");
       }
     */


     this->Detect();
     if (fDetect < 0) {
	  Error("Draw","fDetect < 0 (%s)", fName.Data());
	  return;
     }

     fHist->At(fDetect)->Draw("AXIS");

     TIter next(fHist);
     TString opt = Form("%s,%s", option, "same");
     while (TH1*h=(TH1*)next()) {
	  if (!h) continue;

	  h->UseCurrentStyle();
	  h->SetLineColor(color-1);
	  h->SetLineWidth(4-color);
	  //	h->SetLineStyle(color-1);
	  if (opt.Contains("P")) {
	       h->SetMarkerStyle(color + 18);
	       h->SetMarkerColor(color-1);
	  }
	  h->Draw(opt);
	  color++;
	  //	Info("Draw", "%d", color);
     }

     if (fLineClonesArray) {
	  TIter nextLine(fLineClonesArray->MakeIterator());
	  while (TLine*line=(TLine*)nextLine.Next())
	       line->Draw("same");
     }


}

Int_t K4Stack::GetEntries()
{
     if (!fHist) {
	  Error("GetEntries", "fHist == 0");
	  return 0;
     }
     return fHist->GetEntries();
}


void K4Stack::Locate(TString location,Float_t&x0,Float_t&y0,Float_t&x1,Float_t&y1,Int_t&margin,Bool_t debug)
{//calculate coordinates
     if (location.Contains(",")) {
	  TString sx=TakeString(location,0);
	  TString sy=TakeString(location,1);
	  TString so=TakeString(location,2);
	  TString sm=TakeString(location,3);

	  Int_t x=sx.Atoi();
	  Int_t y=sy.Atoi();
	  Int_t o=so.Atoi();
	  margin=sm.Atoi();

	  if (o==0) Warning("Locate", "Bad location string: %s",location.Data());

	  TCanvas*canvas=new TCanvas(location,location);
	  canvas->Divide(x,y);
	  TPad*pad=(TPad*)canvas->cd(o);
	  x0=pad->GetXlowNDC();
	  y0=pad->GetYlowNDC();
	  x1=x0+pad->GetWNDC();
	  y1=y0+pad->GetHNDC();
	  canvas->Close();
	  delete canvas;

     } else {
	  x0=y0=0.2;
	  x1=y1=0.8;
	  Int_t margin;
	  if (location.Contains("fine")) {
	       x0=.1;y0=.1;x1=.9;y1=.9;
	  } else if (location.Contains("good")) {
	       x0=.2;y0=.2;x1=.8;y1=.8;
	  } else if (location.Contains("head")) {
	       x0=.01;y0=.66;x1=.99;y1=.99;
	  } else if (location.Contains("title")) {
	       this->Locate("1,3,2",x0,y0,x1,y1,margin);
	  } else if (location.Contains("full")) {
	       this->Locate("1,1,1",x0,y0,x1,y1,margin);
	  } else if (location.Contains("l")) {
	       x0=.01;y0=.2;x1=.5;y1=.8;
	  } else if (location.Contains("r")) {
	       x0=.5;y0=.2;x1=.99;y1=.8;
	  } else {;}
     }

     if (debug) Info("Locate", "%f %f %f %f", x0, y0, x1, y1);
}




Int_t K4Stack::CountStrings(TString big,const TString delim)
{
     TObjArray * array=big.Tokenize(delim);
     return array->GetEntriesFast();
}

TString K4Stack::TakeString(TString big,Int_t at,const TString delim)
{
     //returns substring at "at" from a string with commas; returns "" if empty
     TString sub;
     TObjArray*array=big.Tokenize(delim);
     Int_t max=CountStrings(big,delim);
     if (max>at) {
	  TObjString*objString=(TObjString*)array->At(at);
	  sub=objString->GetString();
     }
     return sub;
}



TStyle*K4Stack::Beauty(Float_t labelSize,Int_t titleLocation,Int_t optStat,TString styleName, Int_t color)
{
     labelSize*=0.08;
     Int_t font=42;//see ~/public/rootFonts.ps
     Float_t plus=0.1;

     //    TStyle*style=gROOT->GetStyle(styleName);
     TStyle*style = new TStyle(styleName, styleName);
     //main title!!!
     style->SetTitleStyle(0);//transparent titlebox
     style->SetTitleBorderSize(0);//no frame around the title
     style->SetTitleColor(color);//color of the axis titles
     //axis titles
     style->SetTitleSize(labelSize,"XYZ");//size of X axis title
     style->SetTitleColor(color,"XYZ");//color of the axis
     style->SetTitleFont(font,"XYZ");
     style->SetTitleOffset(1.+plus*5.,"XYZ");//sometimes title overlaps numbers
     //axis labels
     style->SetLabelSize(labelSize, "XYZ");//size of X axis numbers
     style->SetLabelColor(color, "XYZ");//size of X axis numbers
     style->SetNdivisions(7,"XYZ");//make number of ticks reasonable
     //statistick box
     style->SetAxisColor(color, "XYZ");
     style->SetOptStat(optStat);//statistics
     if (optStat>0) {
	  style->SetStatTextColor(color);
	  style->SetStatStyle(0);//transparent statbox
	  style->SetStatY(1.-plus);
	  style->SetStatX(1.-plus);
     }
     //fit statitstics
     style->SetOptFit(0);
     //margins
     style->SetPadTopMargin(plus);
     style->SetPadRightMargin(plus);
     style->SetPadBottomMargin(labelSize*2+plus);
     style->SetPadLeftMargin(labelSize*2+plus);

     //now i want to make use of the title!
     if (titleLocation==1) {//redefined title
	  style->SetOptTitle(1);
	  style->SetTitleX(0.3);
	  style->SetTitleH(0.1);
     } else if (titleLocation==0) {//no title
	  style->SetOptTitle(0);
     } else if (titleLocation==2) {//default title
	  style->SetOptTitle(1);
     } else {//ERROR
	  Error("Beauty","Bad title value");
     }

     style->SetErrorX(0);//no horizontal line for markers
     style->SetEndErrorSize(1);
     style->SetStripDecimals(kFALSE);
     style->SetPalette(1);
     //    style->SetHistMinimumZero(kFALSE);
     //    style->SetHistMinimumZero(kTRUE);
     //    style->SetHeaderPS("gsave 100 -100 t 0 r 0 0 m /Helvetica-Bold findfont 56 sf 0 0 m ( my annotation ) show gr");
     style->SetTitlePS("Tpyn");
     //    style->SetPaperSize(style->kUSLetter);
     //    style->SetOptDate();

     TGaxis::SetMaxDigits(3);
     //    gROOT->SetStyle(styleName);


     /*
     //	TStyle*style=new TStyle(styleName,"hello");

     //    gROOT->SetStyle(styleName);

     style->SetTitleSize(labelSize, "XYZ");//size of the axis titles
     style->SetTitleColor(kBlack,"XYZ");//color of the axis titles
     //    style->SetTitleFont(10,"XYZ");//2,12
     //    style->SetLabelFont(10,"XYZ");//2,12
     style->SetTitleFont(42,"XYZ");//2,12
     //	style->SetLabelFont(62,"XYZ");//2,12
     style->SetLabelFont(42,"X");//2,12
     style->SetLabelFont(42,"Y");//2,12

     //	style->SetCanvasColor(10);	//from Thomas
     style->SetCanvasBorderMode(0);//no shit around canvas
     style->SetPadBorderMode(0);//no shit around pads
     style->SetTitleBorderSize(0);//no shit around the title
     style->SetTitleStyle(0);//transparent titlebox
     style->SetLineScalePS(2);//all lines thickness
     style->SetFillColor(10);//new
     style->SetFrameFillColor(10);//new

     style->SetLabelSize(labelSize, "X");
     style->SetLabelSize(labelSize, "Y");
     style->SetLabelSize(labelSize, "Z");


     style->SetNdivisions(5, "X");
     style->SetNdivisions(5, "Y");
     style->SetNdivisions(5, "Z");

     //	style->SetTitleOffset(1.03,"X");
     //	style->SetTitleOffset(1.5,"Y");
     style->SetPadRightMargin(0.13);
     style->SetPadLeftMargin(0.24);
     style->SetPadTopMargin(0.05);
     style->SetPadBottomMargin(0.20);

     style->SetLineWidth(2);


     style->SetErrorX(0);
     style->SetEndErrorSize(2);

     if (titleLocation == 1) {//inside plot body
     style->SetTitleX(0.2f);
     //	style->SetTitleX(0.2f);
     style->SetTitleY(0.99f);
     style->SetTitleW(0.5f);
     //	style->SetTitleW(1.0f);
     style->SetTitleH(0.1f);
     //	style->SetTitleH(0.2f);
     } else if (titleLocation == 2) {//above the plot
     style->SetTitleX(0.2f);
     style->SetTitleY(1.0f);
     style->SetTitleW(0.8f);
     style->SetTitleH(0.05f);
     } else if (titleLocation == 0) {//no title
     style->SetOptTitle(0);
     } else {//ERROR
     Error("Beauty","Bad values!");
     }
     //stat

     style->SetOptStat(optStat);//statistics
     style->SetStatFontSize(labelSize);
     style->SetStatTextColor(kBlack);
     style->SetStatBorderSize(0);//no shit around the stat
     style->SetStatStyle(0);//transparent statbox
     style->SetStatX(0.95f);
     style->SetStatY(1.01f);
     style->SetStatW(0.5f);
     style->SetStatH(0.1f);


     //	style->SetTextFont(42);
     //	style->SetTextSize(0.055);


     */

     return style;

}

void K4Stack::SetMinimum(Double_t min) {
     if (fDetect < 0) return;
     TH1*h = (TH1*)fHist->At(fDetect);
     h->SetMinimum(min);
     this->Draw();
}

void K4Stack::SetMaximum(Double_t max) {
     if (fDetect < 0) return;
     TH1*h = (TH1*)fHist->At(fDetect);
     h->SetMaximum(max);
     this->Draw();
}

void K4Stack::Fit(TF1*f, TString option)
{

     if (fDetect < 0) return;
     for (Int_t i = 0; i < GetEntries(); ++i) {
	  TH1*h = (TH1*)fHist->At(i);
	  TString name = h->GetName();
	  TString title = h->GetTitle();
	  Info("Fit", "%s %s",name.Data(), title.Data());
	  h->Fit(f, option);
     }
     this->Draw();
}

/*
  void K4Stack::Fit(TString function, Double_t min, Double_t max)
  {
  for (Int_t i = 0; i < this->GetEntries(); ++i) {
  TF1*f = new TF1(function, function, min, max);
  TH1*h = (TH1*)fHist->At(i);
  h->Fit(f, "Q+");
  }
  }
*/
