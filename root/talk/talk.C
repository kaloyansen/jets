{
    
    gROOT->SetBatch();
    TCanvas*canvas = new TCanvas("Kaloyan Krastev (LPSC)", "Moon meeting(11.VII.2022)");
    K4Talk::Instance("moon.pdf", canvas);
    gTalk->Slide("Welcome to the Moon");

    Int_t i = 0;
    while (i < 100000) { 
	gTalk->Slide(Form("%d", i));
	i++;
    }
    gTalk->End();
    return canvas;


}
