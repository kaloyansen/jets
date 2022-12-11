{
    K3Ana * a = new K3Ana();    
//    a->GetFile("/afs/in2p3.fr/home/k/kkrastev/kaloyan_330420.root");
    a->GetFile("~/kaloyan_330420.root");


    Int_t i = 0;
    Int_t p;
    TH1F * h;
    TF1 * f;
    TGraphErrors * g_constant = new TGraphErrors();    
    TGraphErrors * g_mean = new TGraphErrors();
    TGraphErrors * g_sigma = new TGraphErrors();
    TGraphErrors * g;

    gROOT->SetBatch();
    TCanvas * canvas = new TCanvas("Kaloyan Krastev Krastev, LPSC - Grenoble", "CALICE - Grenoble Meeting", 666, 666);
    K4Talk::Instance("fatah.pdf", canvas);
    gTalk->Slide("SiW ECAL Resolution / ADC Randomizer");

    gTalk->Slide("reconstruction");
    gTalk->Draw(a->fC[6]->Identify("trig"), 1, 2, 1, "box");
    gTalk->Draw("
 #bullet ADC values (13 bit);
 #bullet Raw hits [ADC] (after pedestal subtraction);
 #bullet Hits [MIP] (after calibration and noise cut 0.5 MIP);
 #bullet Hits [GeV] (after noise cut 0.6 MIP and conversion);
", 1, 2, 2);

    gTalk->Slide("reconstruction");
    gTalk->Draw(a->fC[6]->Identify("trig"), 1, 2, 1, "box");
    gTalk->Draw("
 #bullet ADC values (13 bit) #color[2]{+ reandomizer(#sigma_{0})};
 #bullet Raw hits [ADC] (after pedestal subtraction);
 #bullet Hits [MIP] (after calibration and noise cut 0.5 MIP);
 #bullet Hits [GeV] (after noise cut 0.6 MIP and conversion);
", 1, 2, 2);


    gTalk->Slide("randomizer(#sigma_{0})");
    gTalk->Style(1);
    i = 0;
    
    // while (a->Loop()) { 
    // 	 h = (TH1F*)gTalk->Draw(a->Identify("fatah"),3, 3, ++i, "P");
    // 	 f = K3Ana::Resolution(h, -2, 2);
    // 	 K3Ana::PrintFitGausParameters(f);
    // }
    gTalk->Draw(a->fC[5]->Identify("fatah"), 2, 2, 1, "HIST");
    gTalk->Draw(a->fC[6]->Identify("fatah"), 2, 2, 2, "HIST");
    gTalk->Draw(a->fC[8]->Identify("fatah"), 2, 2, 3, "HIST");
    gTalk->Draw(a->fC[7]->Identify("fatah"), 2, 2, 4, "HIST");
//    gTalk->DrawLegend(4, 3, 8);

//    gTalk->Draw("c.exp(-0,5 . ((x - #mu) / #sigma ) ^2 )", 3, 3, 6);

    gTalk->Slide("hit multiplicity");
    gTalk->Style(0);
    gTalk->Draw(a->All("mul"), 1, 2, 1, "P");
//    gTalk->DrawLegend(4, 4, 4);
    gTalk->Draw(a->All("mulcut"), 1, 2, 2, "P");
//    gTalk->DrawLegend(4, 4, 12);

    gTalk->Slide("event energy");
    gTalk->Style(1);

    i = 0;
    while (a->Loop()) 
	 gTalk->Draw(a->Identify("energy"), 4, 3, ++i, "HIST,E");
 
 

    gTalk->Slide("energy correction");
    gTalk->Draw(a->fC[6]->Identify("baryxnc"), 3, 2, 1, "HIST,E1");
    gTalk->Draw(a->fC[6]->Identify("baryync"), 3, 2, 2, "HIST,E1");
    gTalk->Draw(a->fC[6]->Identify("baryznc"), 3, 2, 3, "HIST,E1");
    gTalk->Draw(a->fC[6]->Identify("baryx"), 3, 2, 4, "HIST,E1");
    gTalk->Draw(a->fC[6]->Identify("baryy"), 3, 2, 5, "HIST,E1");
    gTalk->Draw(a->fC[6]->Identify("baryz"), 3, 2, 6, "HIST,E1");
    gTalk->Slide("corrected energy");

    i = 0;
    while (a->Loop()) {
	 TString name = a->GetTitle();
	 Float_t shift = atoi(name.Data());
	 if (shift == 0.) p = 0;
	 else if (shift == 1.) p = 1;
	 else if (shift == 2.) p = 2;
	 else if (shift == 3.) p = 3;
	 else if (shift == 4.) p = 4;
	 else if (shift == 5.) p = 5;
	 else if (shift == 6.) p = 6;
	 else if (shift == 7.) p = 7;
	 else if (shift == 8.) p = 8;
	 else if (shift == 10.) p = 9;
	 else if (shift == 13.) p = 10;
	 else if (shift == 17.) p = 11;
	 else gTalk->Error("", Form("shift = %f", shift));

	 gTalk->Info("fatahTalk", Form("%s %f", name.Data(), shift));
	 h = (TH1F*)gTalk->Draw(a->Identify("enecor"),4, 3, ++i, "E");
	 f = K3Ana::Resolution(h, -1, 2);
	 K3Ana::PrintFitGausParameters(f);
	  
	 g_constant->SetPoint(p, shift, f->GetParameter(0));
	 g_mean->SetPoint(p, shift, f->GetParameter(1));
	 g_sigma->SetPoint(p, shift, f->GetParameter(2) * 4.);

	 g_constant->SetPointError(p, 0, f->GetParError(0));
	 g_mean->SetPointError(p, 0, f->GetParError(1));
	 g_sigma->SetPointError(p, 0, f->GetParError(2) * 4.);

	 g_mean->GetYaxis()->SetTitle("energy, GeV");
	 g_sigma->GetYaxis()->SetTitle("energy resolution, %");
	 g_constant->GetXaxis()->SetTitle("#sigma_{0}, ADC counts");
	 g_mean->GetXaxis()->SetTitle("#sigma_{0}, ADC counts");
	 g_sigma->GetXaxis()->SetTitle("#sigma_{0}, ADC counts");

    }

    gTalk->Slide("results and conclusions");
    gTalk->Style();
    f = new TF1("f", "pol3");
    f->SetLineColor(kRed);
    f->SetFillColor(kRed);
    f->SetLineWidth(1);
/* 
    g = (TGraphErrors*)gTalk->Draw(g_constant, 3, 2, 1, "ap");
    g->SetTitle("c");
    g->SetLineColor(kBlue);
    g->SetLineWidth(2);
    g->SetMarkerColor(kBlue);
    g->SetMarkerSize(0.5);
    g->SetMarkerStyle(kFullCircle);
    g->Fit("f");
*/
    g = (TGraphErrors*)gTalk->Draw(g_mean, 2, 2, 1, "ap");
    g->SetTitle("#mu");
    g->SetLineColor(kBlue);
    g->SetLineWidth(2);
    g->SetMarkerColor(kBlue);
    g->SetMarkerSize(0.5);
    g->SetMarkerStyle(kFullCircle);
    g->Fit("f");

    f->SetLineColor(kRed);
    f->SetFillColor(kRed);
    f->SetLineWidth(1);

    g = (TGraphErrors*)gTalk->Draw(g_sigma, 2, 2, 2, "ap");
    g->SetTitle("#sigma");
    g->SetLineColor(kBlue);
    g->SetLineWidth(2);
    g->SetMarkerColor(kBlue);
    g->SetMarkerSize(0.5);
    g->SetMarkerStyle(kFullCircle);
    g->Fit("f");
//    gTalk->Draw(Form("min = %f", f->GetMinimumX(0, 10)), 3, 3, 9);


    gTalk->Draw("
 #bullet SiW ECAL energy response for randomized ADC values was studied;
with 50000 e^{-} data events at 25 GeV;
 #bullet The energy response a.f.o #sigma_{0}(randomizer) was measured;
 #bullet Stable for #sigma_{0} < 7 ADC counts;
 #bullet For larger values of #sigma_{0}:;
   #rightarrow the measured energy increases;
   #rightarrow the energy resolution degrades;
", 1, 2, 2);


    gTalk->SetTravail();
    gTalk->End();
    gSystem->Exit(0);


}
