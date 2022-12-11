{
     gROOT->SetBatch();
     TCanvas * canvas = new TCanvas("", "", 100, 100);
     K4Talk::Instance("houl.pdf", canvas, kOrange);
     gTalk->SetTravail();
     gTalk->Slide();
     gTalk->Slide();
     gTalk->Draw("EN", 1, 1, 1, 1, kBlue, kRed);
     gTalk->Slide();
     gTalk->Draw("FR", 1, 1, 1, 1, kRed, kBlue);
     gTalk->End();
     delete canvas;
     gSystem->Exit(0);

}
