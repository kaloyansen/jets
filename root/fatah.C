{
    bool debug = 0;
    TDatime datime;
    TRandom random(datime.Get());
    TCanvas canvas;
    TH1F h("fatah", "fatah", 55, -10, 10);
    h.Sumw2(); 

    int count = 0;
    while (count < 1000) {
        float f = random.Gaus(0, 3);
        int i = TMath::Nint(f);
        if (debug) cout<<f<<"->"<<i<<endl;
        h.Fill(i);
        h.DrawNormalized("PE1", 1. / h.Integral());
        h.Fit("gaus", "Q");
        canvas.Update();
        count++;
    }
}

