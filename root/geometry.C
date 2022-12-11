{

    TClonesArray*geometry = new TClonesArray("TLorentzVector", 0);
    TClonesArray&g = *geometry;
    for (Int_t i = 0; i < K5Hit::fNumLayer * K5Hit::fNumRow * K5Hit::fNumColumn; ++i) 
	new(g[i]) TLorentzVector();

    Int_t x, y, z;
    TRandom random;
    for (Int_t i = 0; i < K5Hit::fNumLayer * K5Hit::fNumRow * K5Hit::fNumColumn; ++i) {
	TLorentzVector*v4 = (TLorentzVector*)geometry->At(i);
	K5Hit::Decode(x, y, z, i);
	v4->SetX(Double_t(x) + 0.1 * Double_t(z) - 10);
	v4->SetY(Double_t(y) - 10);
	v4->SetZ(Double_t(z) * 10 + 1000);
	v4->SetE(random.Gaus(TMath::Abs(x) * TMath::Abs(y), 3) - 200);
    }
    

    TFile ge("geometry.root", "RECREATE");
    ge.cd();
    geometry->Write("geometry", TObject::kSingleKey);
    ge.ls();
    ge.Close();
    gSystem->Exit(0);
}
