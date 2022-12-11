{
    TGeoManager*g = new TGeoManager("gname", "gtitle");
    TGeoVolume*top = g->MakeBox("Top", 0, 1, 1, 1);
    g->SetTopVolume(top);
    
    //TFile ge("~/data/del.shaojun.geom.root");
    //TFile ge("~/mc/mc.geom.root");
//    TFile ge("~/data/data.shot.root");
    TFile ge("~/mc/mc.shot.root");
    TObjArray*geometry = (TObjArray*)ge.Get("geometry");
    
    UInt_t padsinalayer = K5Hit::fNumColumn * K5Hit::fNumRow;
    Int_t color;
    Int_t column, row, layer;
    for (UInt_t i = 0; i <  geometry->GetEntries(); ++i) {
	TLorentzVector*v4 = (TLorentzVector*)geometry->At(i);
	//for (UInt_t i = 0 * padsinalayer; i < 1 * padsinalayer; ++i) {
	//	K5Hit::Decode(column, row, layer, i);
	//	if (layer < 10) continue;
	//	if (layer > 19) continue;
	//	if (row > 11) continue;
// 	color = 2;
// 	if (column > 5) color ++;
// 	if (column > 11) color ++;
// 	if (row > 5) color ++;
// 	if (row > 11) color ++;
	
//	TLorentzVector*v4 = (TLorentzVector*)geometry->At(i);
	if (v4->X() == 0. && v4->Y() == 0. && v4->Z() == 0.) continue;
	//	color = Int_t(v4->E());
	//	if (color < 1) continue;
	Double_t energy = v4->T();
	//    cout<<energy<<endl;
	if (v4->T() < 0.003) continue;
	color = Int_t(v4->T() * 1000);
	TGeoVolume*cell = g->MakeBox(Form("cell%d", i), 0, 4.8, 4.8, 0.5);
	TGeoTranslation*tgt = new TGeoTranslation(v4->X(), v4->Y(), v4->Z());
	cell->SetLineColor(color);
	top->AddNodeOverlap(cell, i + 1, tgt);
    }

    top->SetVisibility(0);
    g->CloseGeometry();
    
    top->Draw("ogl");
    //    top->Draw("x3d");
//    top->Draw("pad");
    
}
