{
    //    TFile file("~/data/new.data.shot.root");
    TFile file("~/data/new.data.geom.root");
    file.Map();
    Int_t nb = 100;

    TClonesArray*geometry = file->Get("geometry");

    //    geometry->Print();
    Int_t max = geometry->GetEntries();
    //    TGraph2DErrors g2(max);
    TGraph2D g2(max);
    //    g2.SetXTitle("x");
    //    g2.SetYTitle("y");
    //    g2.SetZTitle("z");

    Int_t i = 0;
    while (i < max) {
	TLorentzVector*v4 = geometry->At(i);
	Float_t z = v4->Z();
	if (z < 400) {
	    cout << "empty point at " << i << endl;
	    g2.RemovePoint(i);
	} else {
	    g2.SetPoint(i, v4->X(), v4->Y(), z);
	}

	//	g2.SetPointError(i, v4->E(), v4->E(), v4->E());
	i++;
    }
    //    g2.SetMarkerStyle(25);
    //    g2.SetMarkerSize(0.5);
    //    h3.SetMarkerStyle(21);
    g2.Draw("p0");
    //    g2.GetXaxis()->SetTitle("x");
}
