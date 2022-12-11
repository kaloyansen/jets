{
    TFile*file=new TFile("delMe.root","RECREATE");
    TObject*c = 0;    
    Int_t i = 0;
    while (i < 1000000) {
	if (!c) c = new TObject();//Form("data%d", i),"test beam");
	file->cd();
	c->Write();
	delete c;

	c = 0;
	i++;
    }

    file->Close();
    delete file;
    gSystem->Exit(0);
    
}
