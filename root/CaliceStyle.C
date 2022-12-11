/******************************************************/
/*
  Recommended CALICE style for plots, according to:
  http://www.hep.phy.cam.ac.uk/~drw1/AnalysisNotes/Guidelines.pdf
*/
/******************************************************/

void CaliceStyle()
{
  /*CALICE style for figure: use in a ROOT macro like this:*/
  //gROOT->ProcessLine(".L ~/RootStuff/CaliceStyle.C");
  //CaliceStyle();

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetLabelFont(42,"xyz");
  gStyle->SetTitleFont(42);
  gStyle->SetTitleFont(42,"xyz");
  gStyle->SetStatFont(42);

  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetCanvasColor(kWhite);  
  gStyle->SetOptStat(0); /*don't show statistics box*/
  gStyle->SetTitleSize(0.05, "xyz"); 
  gStyle->SetLegendBorderSize(1);

  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadBottomMargin(0.14);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);

  gROOT->ForceStyle();
}

/***********************************************************************/
/*   Useful functions:                                                 */
/*       set axes title for a histogram                                */
/*                                                                     */
/***********************************************************************/
void SetAxesTitle(TH1 *hist, const char* titlex,const char* titley)
{
  hist->GetXaxis()->SetTitle(titlex);
  hist->GetYaxis()->SetTitle(titley);
}


/***********************************************************************/
/*                                                                     */
/*       draw legend for 1 TGraph or TGraphErrors                      */
/*                                                                     */
/***********************************************************************/
void DrawLegend(TGraph *histo1,
		const Char_t *header,
		const Char_t *label1)
{
  TLegend *legend = new TLegend(0.553482,0.653319,0.950072,0.948683,NULL,"brNDC");
  legend->SetTextAlign(22);/*this is for centering the header*/
                           /*(see root documentation, TAttText constructor)*/
  legend->SetTextFont(42);/*font for the header: 102 -courier bold*/
  legend->SetHeader(header);  /*leg. header (name of histogram or sth. else)*/
  legend->SetTextFont(42);/*font for other legend's entries*/
  
  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"LP");  
  entry1->SetTextColor(histo1->GetLineColor());
  
  legend->SetFillColor(kWhite);
  legend->Draw(); 
}

/***********************************************************************/
/*                                                                     */
/*       draw legend for 1 histo                                       */
/*                                                                     */
/***********************************************************************/
void DrawLegend(TH1 *histo1,
		const Char_t *header,
		const Char_t *label1)
{
  TLegend *legend = new TLegend(0.537356,0.601695,0.899425,0.900424,NULL,"brNDC");
  legend->SetTextAlign(22);
  legend->SetTextFont(42);
  if (header != "")  legend->SetHeader(header); 
  legend->SetTextFont(42);

  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"LPF");  
  entry1->SetTextColor(histo1->GetLineColor());
 
  legend->SetFillColor(kWhite);
  legend->Draw();
  legend->SetBorderSize(1);
}



/***********************************************************************/
/*                                                                     */
/*       draw legend for 2 histos on the same plot                     */
/*                                                                     */
/***********************************************************************/
void Draw2Legend(TH1 *histo1, 
		 TH1 *histo2,
		 const Char_t *label1, 
		 const Char_t *label2,
		 const Char_t *header="")
{

  Float_t max1 = histo1->GetMaximum();
  Float_t max2 = histo2->GetMaximum();
  if (max1 >= max2) histo1->SetMaximum(max1 * 1.1);
  else histo1->SetMaximum(max2 * 1.1);

  TLegend *legend = new TLegend(0.553482,0.653319,0.950072,0.948683,NULL,"brNDC");
  legend->SetTextAlign(22);
  legend->SetTextSize(0.1);
  legend->SetTextSize(0.06);
  
  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"LPF");  
  entry1->SetTextColor(histo1->GetMarkerColor());
  
  TLegendEntry* entry2 = legend->AddEntry(histo2,label2,"LPF");
  entry2->SetTextColor(histo2->GetMarkerColor());

  if (header != "") legend->SetHeader(header); 

  legend->SetFillColor(kWhite); 
  legend->Draw(); 
}


/***********************************************************************/
/*                                                                     */
/*       draw legend for 2 graphs on the same plot                     */
/*                                                                     */
/***********************************************************************/
void Draw2Legend(TGraph *histo1, 
		 TGraph *histo2,
		 const Char_t *label1, 
		 const Char_t *label2,
		 const Char_t *header="")
{
  TLegend *legend = new TLegend(0.574832,0.645657,0.946001,0.93697,NULL,"brNDC");
  legend->SetTextAlign(22);
  legend->SetTextFont(102);
  legend->SetTextSize(0.1);
  if (header != "") legend->SetHeader(header); 
  legend->SetTextSize(0.04);

  legend->SetTextFont(102);
  
  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"LP");  
  entry1->SetTextColor(histo1->GetLineColor());

  TLegendEntry* entry2 = legend->AddEntry(histo2,label2,"LP");
  entry2->SetTextColor(histo2->GetLineColor());

  legend->SetFillColor(kWhite); 
  legend->Draw(); 
}

/***********************************************************************/
/*                                                                     */
/*       draw legend for 3 histos on the same plot                     */
/*                                                                     */
/***********************************************************************/
void Draw3Legend(TH1 *histo1, 
		 TH1 *histo2, 
		 TH1* histo3,
		 const Char_t *label1, 
		 const Char_t *label2, 
		 const Char_t *label3,
		 const Char_t *header="",
		 float fractionYmax = 1.1)
{

  Float_t max1 = histo1->GetMaximum();
  Float_t max2 = histo2->GetMaximum();
  Float_t max3 = histo3->GetMaximum();

  if (max1 < 1.0e+12 && max2 < 1.0e+12 && max3 < 1.0e+12 )
    {
      if (max1 >= max2 && max1 > max3) histo1->SetMaximum(max1 * fractionYmax);
      else if  (max2 >= max1 && max2 > max3) histo1->SetMaximum(max2 * fractionYmax);
      else if  (max3 >= max1 && max3 > max2) histo1->SetMaximum(max3 * fractionYmax);
    }

  TLegend *legend = new TLegend(0.51796,0.650071,0.948994,0.950212,NULL,"brNDC");
  legend->SetTextSize(0.05);
  legend->SetTextAlign(22);
  legend->SetTextFont(42);

  if (header != "")  legend->SetHeader(header); 
 
  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"LPF");  
  entry1->SetTextColor(histo1->GetLineColor());
  
  TLegendEntry* entry2 = legend->AddEntry(histo2,label2,"LPF");
  entry2->SetTextColor(histo2->GetLineColor());

  TLegendEntry* entry3 = legend->AddEntry(histo3,label3,"LPF");
  entry3->SetTextColor(histo3->GetLineColor());

  legend->SetFillColor(kWhite);
  legend->Draw();  

}


/***********************************************************************/
/*                                                                     */
/*       draw legend for 3 histos on the same plot                     */
/*                                                                     */
/***********************************************************************/
void Draw3Legend(TGraph *histo1, 
		 TGraph *histo2, 
		 TGraph* histo3,
		 const Char_t *label1, 
		 const Char_t *label2, 
		 const Char_t *label3,
		 const Char_t *header="",
		 float fractionYmax = 1.1)
{
  TLegend *legend = new TLegend(0.587644,0.650424,0.949713,0.951271,NULL,"brNDC");
  legend->SetTextSize(0.05);
  legend->SetTextAlign(22);
  legend->SetTextFont(42); //102
  legend->SetBorderSize(1);

  if (header != "")  legend->SetHeader(header); 
 
  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"LP");  
  entry1->SetTextColor(histo1->GetLineColor());
  
  TLegendEntry* entry2 = legend->AddEntry(histo2,label2,"LP");
  entry2->SetTextColor(histo2->GetLineColor());

  TLegendEntry* entry3 = legend->AddEntry(histo3,label3,"LP");
  entry3->SetTextColor(histo3->GetLineColor());

  legend->SetFillColor(kWhite);
  legend->Draw();  
  
}





/***********************************************************************/
/*                                                                     */
/*       draw legend for 3 histos on the same plot (lower right)       */
/*                                                                     */
/***********************************************************************/
void Draw3LegendLR(TH1 *histo1, 
		   TH1 *histo2, 
		   TH1* histo3,
		   const Char_t *label1, 
		   const Char_t *label2, 
		   const Char_t *label3,
		   const Char_t *header="")
{

  Float_t max1 = histo1->GetMaximum();
  Float_t max2 = histo2->GetMaximum();
  Float_t max3 = histo3->GetMaximum();

  if (max1 >= max2 && max1 > max3) histo1->SetMaximum(max1*1.10);
  else if  (max2 >= max1 && max2 > max3) histo1->SetMaximum(max2*1.10);
  else if  (max3 >= max1 && max3 > max2) histo1->SetMaximum(max3*1.10);

  TLegend *legend = new TLegend(0.523946,0.168962,0.948994,0.469103,NULL,"brNDC");
  legend->SetTextSize(0.05);
  legend->SetTextFont(102);
  legend->SetTextAlign(22);

  if (header != "")  legend->SetHeader(header); 
 
  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"LPF");  
  entry1->SetTextColor(histo1->GetLineColor());
  
  TLegendEntry* entry2 = legend->AddEntry(histo2,label2,"LPF");
  entry2->SetTextColor(histo2->GetLineColor());

  TLegendEntry* entry3 = legend->AddEntry(histo3,label3,"LPF");
  entry3->SetTextColor(histo3->GetLineColor());

  legend->SetFillColor(kWhite);
  legend->Draw();  
}

/***********************************************************************/
/*                                                                     */
/*       draw legend for 3 histos on the same plot (upper right)       */
/*                                                                     */
/***********************************************************************/
void Draw3LegendUL(TH1 *histo1, 
		   TH1 *histo2, 
		   TH1* histo3,
		   const Char_t *label1, 
		   const Char_t *label2, 
		   const Char_t *label3,
		   const Char_t *header="")
{

  Float_t max1 = histo1->GetMaximum();
  Float_t max2 = histo2->GetMaximum();
  Float_t max3 = histo3->GetMaximum();

  Float_t arr[3] = {max1, max2, max3};
  Float_t max = TMath::MaxElement(3, arr);
  histo1->SetMaximum(max*1.15);

  TLegend *legend = new TLegend(0.170738,0.619174,0.529933,0.919315,NULL,"brNDC");
  legend->SetTextSize(0.05);
  legend->SetTextAlign(22);
  legend->SetTextFont(42);

  if (header != "")  legend->SetHeader(header); 
 
  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"LPF");  
  entry1->SetTextColor(histo1->GetMarkerColor());
  
  TLegendEntry* entry2 = legend->AddEntry(histo2,label2,"LPF");
  entry2->SetTextColor(histo2->GetMarkerColor());

  TLegendEntry* entry3 = legend->AddEntry(histo3,label3,"LPF");
  entry3->SetTextColor(histo3->GetMarkerColor());

  legend->SetFillColor(kWhite);
  legend->Draw();  
}

/***********************************************************************/
/*                                                                     */
/*       draw legend for 4 histos on the same plot                     */
/*                                                                     */
/***********************************************************************/
void Draw4Legend(TH1 *histo1, 
		 TH1 *histo2, 
		 TH1* histo3,
		 TH1* histo4,
		 const Char_t *label1, 
		 const Char_t *label2, 
		 const Char_t *label3, 
		 const Char_t *label4,
		 const Char_t *header="")
{
  Float_t max1 = histo1->GetMaximum();
  Float_t max2 = histo2->GetMaximum();
  Float_t max3 = histo3->GetMaximum();
  Float_t max4 = histo4->GetMaximum();

  Float_t arr[4] = {max1, max2, max3, max4};
  Float_t max = TMath::MaxElement(4, arr);
  histo1->SetMaximum(max*1.15);

  TLegend *legend = new TLegend(0.587644,0.650424,0.949713,0.951271,NULL,"brNDC");
  legend->SetTextAlign(22);
  legend->SetTextFont(42);
  if (header != "")  legend->SetHeader(header); 
  legend->SetTextFont(42);

  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"LPF");  
  entry1->SetTextColor(histo1->GetLineColor());
  
  TLegendEntry* entry2 = legend->AddEntry(histo2,label2,"LP");
  entry2->SetTextColor(histo2->GetLineColor());

  TLegendEntry* entry3 = legend->AddEntry(histo3,label3,"LP");
  entry3->SetTextColor(histo3->GetLineColor());

  TLegendEntry* entry4 = legend->AddEntry(histo4,label4,"LP");
  entry4->SetTextColor(histo4->GetLineColor());

  legend->SetFillColor(kWhite);
  legend->Draw();
  legend->SetBorderSize(1);
}

/***********************************************************************/
/*                                                                     */
/*       draw legend for 4 histos on the same plot (upper left)        */
/*                                                                     */
/***********************************************************************/
void Draw4LegendUL(TH1 *histo1, 
		   TH1 *histo2, 
		   TH1* histo3,
		   TH1* histo4,
		   const Char_t *label1, 
		   const Char_t *label2, 
		   const Char_t *label3, 
		   const Char_t *label4,
		   const Char_t *header="")
{
  Float_t max1 = histo1->GetMaximum();
  Float_t max2 = histo2->GetMaximum();
  Float_t max3 = histo3->GetMaximum();
  Float_t max4 = histo4->GetMaximum();

  Float_t arr[4] = {max1, max2, max3, max4};
  Float_t max = TMath::MaxElement(4, arr);
  histo1->SetMaximum(max*1.15);

  TLegend *legend = new TLegend(0.170738,0.619174,0.529933,0.919315,NULL,"brNDC");
  legend->SetTextAlign(22);
  legend->SetTextFont(42);
  if (header != "")  legend->SetHeader(header); 
  legend->SetTextFont(42);

  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"LPF");  
  entry1->SetTextColor(histo1->GetLineColor());
  
  TLegendEntry* entry2 = legend->AddEntry(histo2,label2,"LP");
  entry2->SetTextColor(histo2->GetLineColor());

  TLegendEntry* entry3 = legend->AddEntry(histo3,label3,"LP");
  entry3->SetTextColor(histo3->GetLineColor());

  TLegendEntry* entry4 = legend->AddEntry(histo4,label4,"LP");
  entry4->SetTextColor(histo4->GetLineColor());

  legend->SetFillColor(kWhite);
  legend->Draw();
  legend->SetBorderSize(1);
}

/***********************************************************************/
/*                                                                     */
/*       draw legend for 5 histos on the same plot                     */
/*                                                                     */
/***********************************************************************/
void Draw5Legend(TH1 *histo1, 
		 TH1 *histo2, 
		 TH1* histo3,
		 TH1* histo4,
		 TH1* histo5,
		 const Char_t *label1, 
		 const Char_t *label2, 
		 const Char_t *label3, 
		 const Char_t *label4,
		 const Char_t *label5,
		 const Char_t *header="")
{
  Float_t max1 = histo1->GetMaximum();
  Float_t max2 = histo2->GetMaximum();
  Float_t max3 = histo3->GetMaximum();
  Float_t max4 = histo4->GetMaximum();
  Float_t max5 = histo5->GetMaximum();

  Float_t arr[5] = {max1, max2, max3, max4, max5};
  Float_t max = TMath::MaxElement(5, arr);
  histo1->SetMaximum(max*1.15);

  TLegend *legend = new TLegend(0.587644,0.650424,0.949713,0.951271,NULL,"brNDC");
  legend->SetTextAlign(22);
  legend->SetTextFont(42);
  if (header != "")  legend->SetHeader(header); 
  legend->SetTextFont(42);

  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"LPF");  
  entry1->SetTextColor(histo1->GetLineColor());
  
  TLegendEntry* entry2 = legend->AddEntry(histo2,label2,"LP");
  entry2->SetTextColor(histo2->GetLineColor());

  TLegendEntry* entry3 = legend->AddEntry(histo3,label3,"LP");
  entry3->SetTextColor(histo3->GetLineColor());

  TLegendEntry* entry4 = legend->AddEntry(histo4,label4,"LP");
  entry4->SetTextColor(histo4->GetLineColor());

  TLegendEntry* entry5 = legend->AddEntry(histo5,label5,"LP");
  entry5->SetTextColor(histo5->GetLineColor());

  legend->SetFillColor(kWhite);
  legend->Draw();
  legend->SetBorderSize(1);
}

/***********************************************************************/
/*                                                                     */
/*       draw legend for 5 histos on the same plot (upper left)        */
/*                                                                     */
/***********************************************************************/
void Draw5LegendUL(TH1 *histo1, 
		   TH1 *histo2, 
		   TH1* histo3,
		   TH1* histo4,
		   TH1* histo5,
		   const Char_t *label1, 
		   const Char_t *label2, 
		   const Char_t *label3, 
		   const Char_t *label4,
		   const Char_t *label5,
		   const Char_t *header="")
{
  Float_t max1 = histo1->GetMaximum();
  Float_t max2 = histo2->GetMaximum();
  Float_t max3 = histo3->GetMaximum();
  Float_t max4 = histo4->GetMaximum();
  Float_t max5 = histo5->GetMaximum();

  Float_t arr[5] = {max1, max2, max3, max4, max5};
  Float_t max = TMath::MaxElement(5, arr);
  histo1->SetMaximum(max*1.15);

  TLegend *legend = new TLegend(0.170738,0.619174,0.529933,0.919315,NULL,"brNDC");
  legend->SetTextAlign(22);
  legend->SetTextFont(42);
  if (header != "")  legend->SetHeader(header); 
  legend->SetTextFont(42);

  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"LPF");  
  entry1->SetTextColor(histo1->GetLineColor());
  
  TLegendEntry* entry2 = legend->AddEntry(histo2,label2,"LP");
  entry2->SetTextColor(histo2->GetLineColor());

  TLegendEntry* entry3 = legend->AddEntry(histo3,label3,"LP");
  entry3->SetTextColor(histo3->GetLineColor());

  TLegendEntry* entry4 = legend->AddEntry(histo4,label4,"LP");
  entry4->SetTextColor(histo4->GetLineColor());

  TLegendEntry* entry5 = legend->AddEntry(histo5,label5,"LP");
  entry5->SetTextColor(histo5->GetLineColor());

  legend->SetFillColor(kWhite);
  legend->Draw();
  legend->SetBorderSize(1);
}

/***********************************************************************/
/*                                                                     */
/*       draw legend for 4 TGraph on the same plot                     */
/*                                                                     */
/***********************************************************************/
void Draw4Legend(TGraph *histo1, 
		 TGraph *histo2, 
		 TGraph* histo3,
		 TGraph* histo4,
		 const Char_t *label1, 
		 const Char_t *label2, 
		 const Char_t *label3, 
		 const Char_t *label4,
		 const Char_t *header="")
{
  Float_t max1 = histo1->GetMaximum();
  Float_t max2 = histo2->GetMaximum();
  Float_t max3 = histo3->GetMaximum();
  Float_t max4 = histo4->GetMaximum();

  Float_t arr[4] = {max1, max2, max3, max4};
  Float_t max = TMath::MaxElement(4, arr);
  histo1->SetMaximum(max*1.15);

  TLegend *legend = new TLegend(0.587644,0.650424,0.949713,0.951271,NULL,"brNDC");
  legend->SetTextAlign(22);
  legend->SetTextFont(42);
  if (header != "")  legend->SetHeader(header); 
  legend->SetTextFont(42);

  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"PL");  
  entry1->SetTextColor(histo1->GetLineColor());
  
  TLegendEntry* entry2 = legend->AddEntry(histo2,label2,"PL");
  entry2->SetTextColor(histo2->GetLineColor());

  TLegendEntry* entry3 = legend->AddEntry(histo3,label3,"PL");
  entry3->SetTextColor(histo3->GetLineColor());

  TLegendEntry* entry4 = legend->AddEntry(histo4,label4,"PL");
  entry4->SetTextColor(histo4->GetLineColor());

  legend->SetFillColor(kWhite);
  legend->Draw();
  legend->SetBorderSize(1);
}
/***********************************************************************/
/*                                                                     */
/*       draw legend for 5 TGraph on the same plot                     */
/*                                                                     */
/***********************************************************************/
void Draw5Legend(TGraph *histo1, 
		 TGraph *histo2, 
		 TGraph* histo3,
		 TGraph* histo4,
		 TGraph* histo5,
		 const Char_t *label1, 
		 const Char_t *label2, 
		 const Char_t *label3, 
		 const Char_t *label4,
		 const Char_t *label5,
		 const Char_t *header="")
{
  Float_t max1 = histo1->GetMaximum();
  Float_t max2 = histo2->GetMaximum();
  Float_t max3 = histo3->GetMaximum();
  Float_t max4 = histo4->GetMaximum();
  Float_t max5 = histo5->GetMaximum();

  Float_t arr[5] = {max1, max2, max3, max4, max5};
  Float_t max = TMath::MaxElement(5, arr);
  histo1->SetMaximum(max*1.15);

  TLegend *legend = new TLegend(0.587644,0.650424,0.949713,0.951271,NULL,"brNDC");
  legend->SetTextAlign(22);
  legend->SetTextFont(42);
  if (header != "")  legend->SetHeader(header); 
  legend->SetTextFont(42);

  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"PL");  
  entry1->SetTextColor(histo1->GetLineColor());
  
  TLegendEntry* entry2 = legend->AddEntry(histo2,label2,"PL");
  entry2->SetTextColor(histo2->GetLineColor());

  TLegendEntry* entry3 = legend->AddEntry(histo3,label3,"PL");
  entry3->SetTextColor(histo3->GetLineColor());

  TLegendEntry* entry4 = legend->AddEntry(histo4,label4,"PL");
  entry4->SetTextColor(histo4->GetLineColor());

  TLegendEntry* entry5 = legend->AddEntry(histo5,label5,"PL");
  entry5->SetTextColor(histo5->GetLineColor());

  legend->SetFillColor(kWhite);
  legend->Draw();
  legend->SetBorderSize(1);
}

/***********************************************************************/
/*                                                                     */
/*       draw legend for 6 TGraph on the same plot                     */
/*                                                                     */
/***********************************************************************/
void Draw6Legend(TGraph *histo1, 
		 TGraph *histo2, 
		 TGraph* histo3,
		 TGraph* histo4,
		 TGraph* histo5,
		 TGraph* histo6,
		 const Char_t *label1, 
		 const Char_t *label2, 
		 const Char_t *label3, 
		 const Char_t *label4,
		 const Char_t *label5,
		 const Char_t *label6,
		 const Char_t *header="")
{
  Float_t max1 = histo1->GetMaximum();
  Float_t max2 = histo2->GetMaximum();
  Float_t max3 = histo3->GetMaximum();
  Float_t max4 = histo4->GetMaximum();
  Float_t max5 = histo5->GetMaximum();
  Float_t max6 = histo6->GetMaximum();

  Float_t arr[6] = {max1, max2, max3, max4, max5, max6};
  Float_t max = TMath::MaxElement(6, arr);
  histo1->SetMaximum(max*1.15);

  TLegend *legend = new TLegend(0.587644,0.650424,0.949713,0.951271,NULL,"brNDC");
  legend->SetTextAlign(22);
  legend->SetTextFont(42);
  if (header != "")  legend->SetHeader(header); 
  legend->SetTextFont(42);

  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"PL");  
  entry1->SetTextColor(histo1->GetLineColor());
  
  TLegendEntry* entry2 = legend->AddEntry(histo2,label2,"PL");
  entry2->SetTextColor(histo2->GetLineColor());

  TLegendEntry* entry3 = legend->AddEntry(histo3,label3,"PL");
  entry3->SetTextColor(histo3->GetLineColor());

  TLegendEntry* entry4 = legend->AddEntry(histo4,label4,"PL");
  entry4->SetTextColor(histo4->GetLineColor());

  TLegendEntry* entry5 = legend->AddEntry(histo5,label5,"PL");
  entry5->SetTextColor(histo5->GetLineColor());

  TLegendEntry* entry6 = legend->AddEntry(histo6,label6,"PL");
  entry6->SetTextColor(histo6->GetLineColor());

  legend->SetFillColor(kWhite);
  legend->Draw();
}


/***********************************************************************/
/*                                                                     */
/*       draw legend for 6 histos on the same plot                     */
/*                                                                     */
/***********************************************************************/
void Draw6Legend(TH1 *histo1, 
		 TH1 *histo2, 
		 TH1* histo3,
		 TH1* histo4,
		 TH1* histo5,
		 TH1* histo6,
		 const Char_t *label1, 
		 const Char_t *label2, 
		 const Char_t *label3, 
		 const Char_t *label4,
		 const Char_t *label5,
		 const Char_t *label6,
		 const Char_t *header="")
{
  Float_t max1 = histo1->GetMaximum();
  Float_t max2 = histo2->GetMaximum();
  Float_t max3 = histo3->GetMaximum();
  Float_t max4 = histo4->GetMaximum();
  Float_t max5 = histo5->GetMaximum();
  Float_t max6 = histo6->GetMaximum();

  Float_t arr[6] = {max1, max2, max3, max4, max5, max6};
  Float_t max = TMath::MaxElement(6, arr);
  histo1->SetMaximum(max*1.15);

  TLegend *legend = new TLegend(0.587644,0.650424,0.949713,0.951271,NULL,"brNDC");
  legend->SetTextAlign(22);
  legend->SetTextFont(42);
  if (header != "")  legend->SetHeader(header); 
  legend->SetTextFont(42);

  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"PL");  
  entry1->SetTextColor(histo1->GetLineColor());
  
  TLegendEntry* entry2 = legend->AddEntry(histo2,label2,"PL");
  entry2->SetTextColor(histo2->GetLineColor());

  TLegendEntry* entry3 = legend->AddEntry(histo3,label3,"PL");
  entry3->SetTextColor(histo3->GetLineColor());

  TLegendEntry* entry4 = legend->AddEntry(histo4,label4,"PL");
  entry4->SetTextColor(histo4->GetLineColor());

  TLegendEntry* entry5 = legend->AddEntry(histo5,label5,"PL");
  entry5->SetTextColor(histo5->GetLineColor());

  TLegendEntry* entry6 = legend->AddEntry(histo6,label6,"PL");
  entry6->SetTextColor(histo6->GetLineColor());

  legend->SetFillColor(kWhite);
  legend->Draw();
}





/***********************************************************************/
/*                                                                     */
/*       draw legend for 7 TGraph on the same plot                     */
/*                                                                     */
/***********************************************************************/
void Draw7Legend(TGraph *histo1, 
		 TGraph *histo2, 
		 TGraph* histo3,
		 TGraph* histo4,
		 TGraph* histo5,
		 TGraph* histo6,
		 TGraph* histo7,
		 const Char_t *label1, 
		 const Char_t *label2, 
		 const Char_t *label3, 
		 const Char_t *label4,
		 const Char_t *label5,
		 const Char_t *label6,
		 const Char_t *label7,
		 const Char_t *header="")
{
  Float_t max1 = histo1->GetMaximum();
  Float_t max2 = histo2->GetMaximum();
  Float_t max3 = histo3->GetMaximum();
  Float_t max4 = histo4->GetMaximum();
  Float_t max5 = histo5->GetMaximum();
  Float_t max6 = histo6->GetMaximum();
  Float_t max7 = histo7->GetMaximum();

  Float_t arr[7] = {max1, max2, max3, max4, max5, max6, max7};
  Float_t max = TMath::MaxElement(7, arr);
  histo1->SetMaximum(max*1.15);

  TLegend *legend = new TLegend(0.587644,0.650424,0.949713,0.951271,NULL,"brNDC");
  legend->SetTextAlign(22);
  legend->SetTextFont(42);
  if (header != "")  legend->SetHeader(header); 
  legend->SetTextFont(42);

  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"PL");  
  entry1->SetTextColor(histo1->GetLineColor());
  
  TLegendEntry* entry2 = legend->AddEntry(histo2,label2,"PL");
  entry2->SetTextColor(histo2->GetLineColor());

  TLegendEntry* entry3 = legend->AddEntry(histo3,label3,"PL");
  entry3->SetTextColor(histo3->GetLineColor());

  TLegendEntry* entry4 = legend->AddEntry(histo4,label4,"PL");
  entry4->SetTextColor(histo4->GetLineColor());

  TLegendEntry* entry5 = legend->AddEntry(histo5,label5,"PL");
  entry5->SetTextColor(histo5->GetLineColor());

  TLegendEntry* entry6 = legend->AddEntry(histo6,label6,"PL");
  entry6->SetTextColor(histo6->GetLineColor());

  TLegendEntry* entry7 = legend->AddEntry(histo7,label7,"PL");
  entry7->SetTextColor(histo7->GetLineColor());

  legend->SetFillColor(kWhite);
  legend->Draw();
}




/***********************************************************************/
/*                                                                     */
/*       draw legend for 7 histos on the same plot                     */
/*                                                                     */
/***********************************************************************/
void Draw7Legend(TH1 *histo1, 
		 TH1 *histo2, 
		 TH1* histo3,
		 TH1* histo4,
		 TH1* histo5,
		 TH1* histo6,
		 TH1* histo7,
		 const Char_t *label1, 
		 const Char_t *label2, 
		 const Char_t *label3, 
		 const Char_t *label4,
		 const Char_t *label5, 
		 const Char_t *label6,
		 const Char_t *label7,
		 const Char_t *header="")
{
  Float_t max1 = histo1->GetMaximum();
  Float_t max2 = histo2->GetMaximum();
  Float_t max3 = histo3->GetMaximum();
  Float_t max4 = histo4->GetMaximum();
  Float_t max5 = histo5->GetMaximum();
  Float_t max6 = histo6->GetMaximum();
  Float_t max7 = histo7->GetMaximum();

  Float_t arr[7] = {max1, max2, max3, max4, max5, max6, max7};
  Float_t max = TMath::MaxElement(7, arr);
  histo1->SetMaximum(max*1.15);
 
  Float_t max1 = histo1->GetMaximum();
  Float_t max2 = histo2->GetMaximum();
  Float_t max3 = histo3->GetMaximum();
 
  if (max1 > max2 && max1 > max3) histo1->SetMaximum(max1*1.5);
  else if  (max2 > max1 && max2 > max3) histo1->SetMaximum(max2*1.5);
  else if  (max3 > max1 && max3 > max2) histo1->SetMaximum(max3*1.5);

  TLegend *legend = new TLegend(0.587644,0.650424,0.949713,0.951271,NULL,"brNDC");
  legend->SetTextAlign(22);
  legend->SetTextFont(42);
  if (header != "")  legend->SetHeader(header); 
  legend->SetTextFont(42);

  TLegendEntry* entry1 = legend->AddEntry(histo1,label1,"L");  
  entry1->SetTextColor(histo1->GetLineColor());
  
  TLegendEntry* entry2 = legend->AddEntry(histo2,label2,"L");
  entry2->SetTextColor(histo2->GetLineColor());

  TLegendEntry* entry3 = legend->AddEntry(histo3,label3,"L");
  entry3->SetTextColor(histo3->GetLineColor());

  TLegendEntry* entry4 = legend->AddEntry(histo4,label4,"L");
  entry4->SetTextColor(histo4->GetLineColor());

  TLegendEntry* entry5 = legend->AddEntry(histo5,label5,"L");
  entry5->SetTextColor(histo5->GetLineColor());

  TLegendEntry* entry6 = legend->AddEntry(histo6,label6,"L");
  entry6->SetTextColor(histo6->GetLineColor());

  TLegendEntry* entry7 = legend->AddEntry(histo7,label7,"L");
  entry7->SetTextColor(histo7->GetLineColor());

  legend->SetFillColor(kWhite);
  legend->Draw();
}


/***********************************************************************/
/*                                                                     */
/*       draw a text box, for example "CALICE preliminary"             */
/*                                                                     */
/***********************************************************************/
void DrawText(TString string)
{
  TPaveText *pt = new TPaveText(0.10, 0.91, 0.43, 0.96, "tbNDC");
  pt->SetTextSize(0.03);
  pt->SetFillColor(0);
  pt->SetBorderSize(1.);
  pt->SetTextAlign(22); //center
  pt->AddText(string);
  pt->Draw();

  pt->SetTextFont(102);
 
}


/***********************************************************************/
/*                                                                     */
/*       print parameters of a Gaussian fit                            */
/*                                                                     */
/***********************************************************************/
void PrintFitGausParameters(TF1* fitfctn)
{
  TPaveText *pt = new TPaveText(0.383985,0.612734,0.866147,0.842713,"tbNDC");
  pt->SetTextSize(0.04);
  pt->SetFillColor(0);
  pt->SetTextAlign(12);
  pt->SetBorderSize(1);

  TText *pte;
  /*char array to hold the legend's entries:*/
  char display[50];

  /*extract the fit parameters*/
  Double_t p0 = fitfctn->GetParameter(0);
  Double_t e0 = fitfctn->GetParError(0);
  sprintf(display, "const = %5.2f #\pm %3.2f", p0, e0);
  pte = pt->AddText(display);

  Double_t p1 = fitfctn->GetParameter(1);
  Double_t e1 = fitfctn->GetParError(1);
  sprintf(display, "#mu = %5.4f #\pm %3.2f", p1, e1);
  pte = pt->AddText(display);

  Double_t p2 = fitfctn->GetParameter(2);
  Double_t e2 = fitfctn->GetParError(2);
  sprintf(display, "#sigma = %5.4f #\pm %3.2f", p2, e2);
  pte = pt->AddText(display);

  pt->SetTextFont(102);
  pt->Draw();

}
