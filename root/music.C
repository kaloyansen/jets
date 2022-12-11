{
    Int_t max = 24;
    max = 8;
    TGraph g;
    g.SetTitle("Frequency");
    for (Int_t i = 0; i < max; ++i) 
	g.SetPoint(i, 12*i, pow(2, i));
    TCanvas c;
    g.Draw("ac*");

    TF1*fit = new TF1("fit", "pow(2, ([0]*x))");
    g.Fit(fit, "", "", 0.1, pow(2, max));
    Double_t p = 1.0 / 12;
    Info("fit", "2^([0]*x)");
    Info("note", "1 / 12 = %f", p);
}
