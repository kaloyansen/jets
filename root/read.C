{

    //read    
    TFile*controlFile=new TFile("data.root","READ");
    K3Control*control=(K3Control*)controlFile->Get("data");
    control->Glist();

    TCanvas canvas;
    canvas.Divide(2,2);
    canvas.cd(1);
    control->Draw("h1");
    canvas.cd(2);
    control->Draw("h2","box");
    canvas.cd(3);
    control->Draw("h3","box");
    canvas.Update();

    controlFile->Close();
    delete controlFile;
    gSystem->Sleep(10000);
    gSystem->Exit(0);

}
