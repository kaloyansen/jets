{

    K3Ana*a = new K3Ana();    a->GetFile("~/data/new.data.control.root");
    K3Ana*b = new K3Ana();    b->GetFile("~/mc/smear0.0.control.root");
    K3Ana*c = new K3Ana();    c->GetFile("~/mc/smear0.5.control.root");
    K3Ana*d = new K3Ana();    d->GetFile("~/mc/smear1.0.control.root");
    K3Ana*e = new K3Ana();    e->GetFile("~/mc/smear1.5.control.root");
    K3Ana*g = new K3Ana();    g->GetFile("~/mc/smear0.6.control.root");
    K3Ana*h = new K3Ana();    h->GetFile("~/mc/smear1.1.control.root");
    K3Ana*m = new K3Ana();    m->GetFile("~/mc/smear0.9.control.root");
    K3Ana*n = new K3Ana();    n->GetFile("~/mc/smear0.8.control.root");



    Double_t ygap = -8.58;
    Double_t xgap1 = -31.11;
    Double_t xgap2 = 32.41;



    K4Stack*k;
    //    TMultiGraph*resolution;
    TF1*gapx1function = new TF1("gapx1function", "1-[0]*exp(-0.5*((x-[1])/[2])**2)", -40, -10);
    TF1*gapx2function = new TF1("gapx2function", "1-[0]*exp(-0.5*((x-[1])/[2])**2)", 10, 40);
    TF1*gapyfunction = new TF1("gapyfunction", "1-[0]*exp(-0.5*((x-[1])/[2])**2)", -20, 5);
    TF1*mapx1function = new TF1("mapx1function", "1-[0]*exp(-0.5*((x-[1])/[2])**2)", -40, -10);
    TF1*mapx2function = new TF1("mapx2function", "1-[0]*exp(-0.5*((x-[1])/[2])**2)", 10, 40);
    TF1*mapyfunction = new TF1("mapyfunction", "1-[0]*exp(-0.5*((x-[1])/[2])**2)", -20, 5);
    TF1*gaus = new TF1("gaus", "gaus", -20, 20);
    gapx1function->SetParameters(0.1, -30, 3);
    gapx2function->SetParameters(0.1, 30, 5);
    gapyfunction->SetParameters(0.3, -9, 3);
    mapx1function->SetParameters(0.1, -30, 3);
    mapx2function->SetParameters(0.1, 30, 5);
    mapyfunction->SetParameters(0.3, -9, 3);

    gapx1function->SetLineStyle(1);
    gapx2function->SetLineStyle(1);
    gapyfunction->SetLineStyle(1);
    gapx1function->SetLineWidth(1);
    gapx2function->SetLineWidth(1);
    gapyfunction->SetLineWidth(1);

    mapx1function->SetLineStyle(1);
    mapx2function->SetLineStyle(1);
    mapyfunction->SetLineStyle(1);
    mapx1function->SetLineWidth(1);
    mapx2function->SetLineWidth(1);
    mapyfunction->SetLineWidth(1);

    //    const Int_t nsta = 12;
    //    K4Stack*sta[nsta];
    //    for (Int_t i = 0; i < nsta; i++) sta[i] = new K4Stack();

    Info("talk", "Resolution measurement...");


    TClonesArray*stax = new TClonesArray("K4Stack", 0);


    Info("talk", "x");
    TMultiGraph*xresolution = new TMultiGraph();
    TMultiGraph*xxresolution = new TMultiGraph();
    TMultiGraph*yresolution = new TMultiGraph();
    TMultiGraph*yyresolution = new TMultiGraph();
    TMultiGraph*eresolution = new TMultiGraph();


    Info("talk", "before a");
    xresolution->Add(a->Resolution("h1deltalinx+safe", kTRUE, stax, "DATA"));
    Info("talk", "after a");
    xresolution->Add(b->Resolution("h1deltalinx+safe", kTRUE, stax, "MC+0.0 mm"));
    xresolution->Add(c->Resolution("h1deltalinx+safe", kTRUE, 0,    "MC+0.5 mm"));
    xresolution->Add(d->Resolution("h1deltalinx+safe", kTRUE, stax, "MC+1.0 mm"));
    xresolution->Add(e->Resolution("h1deltalinx+safe", kTRUE, 0,    "MC+1.5 mm"));

    xxresolution->Add(g->Resolution("h1deltalinx+safe", kTRUE, 0, "MC:0.6sqrt(1/E+1)"));
    xxresolution->Add(h->Resolution("h1deltalinx+safe", kTRUE, 0, "MC:1.1sqrt(1/E+1)"));
    xxresolution->Add(a->Resolution("h1deltalinx+safe", kTRUE, 0, "DATA"));
    xxresolution->Add(n->Resolution("h1deltalinx+safe", kTRUE, 0, "MC:0.8sqrt(1/E+1)"));
    xxresolution->Add(m->Resolution("h1deltalinx+safe", kTRUE, 0, "MC:0.9sqrt(1/E+1)"));
    xxresolution->Add(b->Resolution("h1deltalinx+safe", kTRUE, 0, "MC+0.0 mm"));

    yresolution->Add(a->Resolution("h1deltaliny+safe", kTRUE, stax, "DATA"));
    yresolution->Add(b->Resolution("h1deltaliny+safe", kTRUE, stax, "MC+0.0 mm"));
    yresolution->Add(c->Resolution("h1deltaliny+safe", kTRUE, 0,    "MC+0.5 mm"));
    yresolution->Add(d->Resolution("h1deltaliny+safe", kTRUE, stax, "MC+1.0 mm"));
    yresolution->Add(e->Resolution("h1deltaliny+safe", kTRUE, 0,    "MC+1.5 mm"));

    yyresolution->Add(g->Resolution("h1deltaliny+safe", kTRUE, 0, "MC:0.6sqrt(1/E+1)"));
    yyresolution->Add(h->Resolution("h1deltaliny+safe", kTRUE, 0, "MC:1.1sqrt(1/E+1)"));
    yyresolution->Add(a->Resolution("h1deltaliny+safe", kTRUE, 0, "DATA"));
    yyresolution->Add(n->Resolution("h1deltaliny+safe", kTRUE, 0, "MC:0.8sqrt(1/E+1)"));
    yyresolution->Add(m->Resolution("h1deltaliny+safe", kTRUE, 0, "MC:0.9sqrt(1/E+1)"));
    yyresolution->Add(b->Resolution("h1deltaliny+safe", kTRUE, 0, "MC+0.0 mm"));

    eresolution->Add(a->Resolution("h1deltae+corrected", kFALSE, 0, "DATA/cor."));
    eresolution->Add(b->Resolution("h1deltae+corrected", kFALSE, 0, "MC/cor."));


    Info("talk", "after a");
    xresolution->SetMinimum(0); xresolution->SetMaximum(2);    K3Ana::Resolution(xresolution, "");
    xxresolution->SetMinimum(0);  xxresolution->SetMaximum(2);  K3Ana::Resolution(xxresolution, "");
    yresolution->SetMinimum(0);  yresolution->SetMaximum(2);  K3Ana::Resolution(yresolution, "Q");
    yyresolution->SetMinimum(0);  yyresolution->SetMaximum(2);  K3Ana::Resolution(yyresolution, "Q");
    K3Ana::Resolution(eresolution, "Q");



//     K4Stack*dummy = new K4Stack();
//     K4Stack*xdummy = new K4Stack();
//     K4Stack*xmummy = new K4Stack();
//     K4Stack*ydummy = new K4Stack();
//     K4Stack*ymummy = new K4Stack();

    gROOT->SetBatch();

    TCanvas*canvas = new TCanvas("Kaloyan Krastev(LPSC)", "CALICE Analysis(23.XI.2009)", 800, 500);


    Info("talk", "before talk");
    K4Talk::Instance("kaloyan.pdf", canvas);
    gTalk->Beauty(1, 0, 0);

    /*
    Int_t*energy = new Int_t[a->GetN()];
    Double_t*e = new Double_t[a->GetN()];
    while (a->Loop()) {
	//	TString name = a->GetName();
	TString title = a->GetTitle();
	//	name.ReplaceAll("test", "");	
	//	energy[a->fI] = name.Atoi();
	energy[a->fI] = title.Atoi();
	//	e[a->fI] = Double_t(energy[a->fI]);
	Info("talk", "%d %d GeV", a->fI, energy[a->fI]);
    }
    */

    gTalk->Slide("Si-W Resolution /CERN 2006/");

    /* 
    gTalk->Slide("Motivation");
    gTalk->Draw("According to the PFA, neutral flow is reconstructed in calrimeter;Charged flow is isolated and reconstructed in tracker;Both ECAL energy and spatiol resolution are importangTalk->;Space resolution has not been measured yegTalk->;Beam test data collected at CERN and Fermilab are available.", 1, 3, 2);
    */

    /*    
    Info("","Gonna draw");
    gT->Slide("Shower");
    gT->DrawImage("viewer.png", 2, 1, 2);
    Info("","ok");
    */

    /*
    gT->Slide("The CALICE Si-W ECAL prototype");
    

    
    gT->Draw(a->All("h3pads", "yx"), 2, 2, 1, "col");
    gT->DrawLine(-90, ygap, 92, ygap);
    gT->DrawLine(xgap1, -64.5, xgap1, 47.65);
    gT->DrawLine(xgap2, -64.5, xgap2, 47.75);

    gT->Draw(a->All("h3pads", "yz"), 2, 2, 3, "col");
    gT->DrawLine(750, ygap, 975, ygap);

    gT->Draw(a->All("h3pads", "xz"), 2, 2, 4, "col");
    gTalk->DrawLine(750, xgap1, 975, xgap1);
    gTalk->DrawLine(750, xgap2, 975, xgap2);
    
    gTalk->Draw("30 layers with 3 x 2 wafers with 6 x 6 pads; In total: 6480 pads, 10 x 10 mm^{2} each;layers aligned in y but shifted in x; absorber: 1.4 mm (layer 0 - 9), 2.8 mm (layer 10 - 19), 4.2 mm (layer 20 - 19); Inter-wafer gaps  ~  1 mm", 2, 2, 2, 1, kBlack);

    //    gTalk->DrawImage("viewer.png", 2, 2, 1);


//     gTalk->Slide("Data samples (CERN 2006)");
//     gTalk->Draw(a->All("h1beamenergy"), 2, 2, 1, "HIST");
//     gTalk->Draw(a->All("h1hitenergy"), 2, 2, 2, "HIST");
//     gTalk->Logy();
//     gTalk->Draw(a->All("h2nhitevenergy+electron"), 2, 2, 3, "BOX");
//     gTalk->Draw(a->All("h1ntrack"), 2, 2, 4, "HIST");
//     gTalk->Logy();
*/

    gTalk->Slide("position resolution");
    gTalk->Draw("
1. Calculate energy weighted mean shower position, #vec{b} = #sum_{hits} #vec{r_{i}} w_{i} / #sum_{hits} w_{i};
2. Use track reconstructed in drift chambers as reference;
3. Measure the distance from #vec{b} to reference track;4. Fit distance distribution to Gaus
", 1, 5, 2);
    gTalk->Draw("
** From previous measurements at LPSC;
** MC predicts better resolution (0.8mm);
I will add noise to the hits in drift chambers for MC;
to account for the finite resolution of the drift chambers;
", 1, 5, 4, 1, kBlack);


    gTalk->Slide("data");
    gTalk->Draw("data 2006", 6, 6, 3, 1, kBlack);
    gTalk->Draw("data 2006", 6, 6, 6, 1, kBlack);
    gTalk->Draw("Monte Carlo", 6, 6, 21, .1, kBlack);
    gTalk->Draw("Monte Carlo", 6, 6, 24, 2, kBlack);

    k = (K4Stack*)gTalk->Draw(a->All("h1ehit"), 2, 2, 2, "HIST,E1");
    if (k) k->SetMinimum(1);
    gTalk->Logy();
    gTalk->Draw(a->All("h1ee+all"), 2, 2, 1, "HIST,E1");

    k = (K4Stack*)gTalk->Draw(b->All("h1ehit"), 2, 2, 4, "HIST,E1");
    if (k) k->SetMinimum(1);
    gTalk->Logy();
    gTalk->Draw(b->All("h1ee+all"), 2, 2, 3, "HIST,E1");


    gTalk->Slide();

    gTalk->Draw("
data from:;
/grid/calice/tb-cern/rec/rec_v0406/Run310056_rec.0406.000.slcio;
/grid/calice/tb-cern/rec/rec_v0406/Run300202_rec.0406.000.slcio;
/grid/calice/tb-cern/rec/rec_v0406/Run300236_rec.0406.000.slcio;
/grid/calice/tb-cern/rec/rec_v0406/Run300207_rec.0406.000.slcio;
/grid/calice/tb-cern/rec/rec_v0406/Run300235_rec.0406.000.slcio;
/grid/calice/tb-cern/rec/rec_v0406/Run300384_rec.0406.000.slcio; 
official Monte Carlo (Thanks to Shaojun!):;
/grid/calice/shaojun;
", 1, 1, 1, 1, kBlue);
    


    
    //    gTalk->Draw("linear weights: w_{i} = E_{i} / E_{tot}", 2, 4, 3, 1, kBlue);
    //    gTalk->Draw("logarithmic weights:;w_{i} = max{0, w0 + log(E_{i} / E_{tot})}", 2, 4, 4, 1, kBlue);

    //    gTalk->Slide("Spatial resolution");
    //    gTalk->Draw("1. Calculate energy weighted mean shower position, #vec{b} = #sum_{hits} #vec{r_{i}} w_{i} / #sum_{hits} w_{i};2. Measure distance (#vec{b} #rightarrow track from drift chambers);3. Fit distance to Gaus", 1, 4, 1, 1, kBlack);
    //    gTalk->Draw("linear weights: w_{i} = E_{i} / E_{tot}", 2, 4, 3, 1, kBlue);
    /*
    k = new K4Stack("dfdsca");
    k->Add(a->Sum("h3bclin+electron", "fds", "x"));
    k->Add(b->Sum("h3bclin+electron", "fds", "x"));
    k->NormalizeTo(1);
    gTalk->Draw(k, 3, 2, 4, "HIST,E1");

    k = new K4Stack("dfdscb");
    k->Add(a->Sum("h3bclin+electron", "fds", "y"));
    k->Add(b->Sum("h3bclin+electron", "fds", "y"));
    k->NormalizeTo(1);
    gTalk->Draw(k, 3, 2, 5, "HIST,E1");

    k = new K4Stack("dfdscc");
    k->Add(a->Sum("h3bclin+electron", "fds", "z"));
    k->Add(b->Sum("h3bclin+electron", "fds", "z"));
    k->NormalizeTo(1);
    gTalk->Draw(k, 3, 2, 6, "HIST,E1");

    gTalk->Draw("+ data",                                    6, 15, 47, 0.1, kBlack);
    gTalk->Draw("+ MC",                                      6, 15, 53, 0.1, kRed);
    */
    //    gTalk->Slide("#vec{b}");
    //    gTalk->Beauty(0.8, 0, 0);
//     gTalk->DrawLine(-90, ygap, 92, ygap);
//     gTalk->DrawLine(xgap1, -64.5, xgap1, 47.65);
//     gTalk->DrawLine(xgap2, -64.5, xgap2, 47.75);
//    gTalk->Draw(a->Sum("h3bclin+electron", "yz"), 3, 2, 2, "col");
//     gTalk->DrawLine(800, ygap, 900, ygap);
//    gTalk->Draw(a->All("h3bclin+electron", "xz"), 3, 2, 3, "col");
//     gTalk->DrawLine(800, xgap1, 900, xgap1);
//     gTalk->DrawLine(800, xgap2, 900, xgap2);

//    gTalk->Draw("#uparrow Data / Monte Carlo #downarrow", 3, 3, 5, 1, kBlack);
//    gTalk->Slide("#vec{b}");
//    gTalk->Draw(b->Sum("h3bclin+electron", "fds", "x"), 3, 2, 4, "HIST,E1");
//     gTalk->DrawLine(-90, ygap, 92, ygap);
//     gTalk->DrawLine(xgap1, -64.5, xgap1, 47.65);
//     gTalk->DrawLine(xgap2, -64.5, xgap2, 47.75);
//    gTalk->Draw(b->Sum("h3bclin+electron", "yz"), 3, 2, 5, "col");
    //    gTalk->DrawLine(800, ygap, 900, ygap);
    //    gTalk->Draw(b->All("h3bclin+electron", "xz"), 3, 2, 6, "col");
//     gTalk->DrawLine(800, xgap1, 900, xgap1);
//     gTalk->DrawLine(800, xgap2, 900, xgap2);


    
    gTalk->Slide("analysis");
    //    gTalk->Draw("1. Ignore hits with E_{i} <= 0.6 MIP;2. Account for absorber E_{i} * 1/2/3;3. Correct event energy: #sum E_{i} for interwafer gaps;
    gTalk->Draw("
/***** parameters *****/;
//const Double_t alpha[3] = {1.1, 2, 2.7}//compensation coefficients;
const Double_t alpha[3] = {1, 2, 3}//compensation coefficients;
const Double_t beta = 250//MIP/GeV;
const Double_t gamma = 7000//MIP/GeV(Monte Carlo);
// ;
/***** selection ******/;
E_hit > 0.6 MIP;
0.8 * E_beam < E < 1.2 * E_beam;
b_x - gap_x > 17.2;
b_y - gap_y > 12.76;
n_tracks = 1;


", 1, 1, 1, 0.8, kBlack);



    gTalk->Slide("wafer gaps correction");
    k = (K4Stack*)gTalk->Draw(a->Similar("p1gapx"), 2, 2, 1);
    if (k) {
	k->Fit(gapx1function, "QR+");
	k->Fit(gapx2function, "QR+");
	k->SetMinimum(0.6);
	k->SetMaximum(1.2);
    }
    k = (K4Stack*)gTalk->Draw(a->Similar("p1gapy"), 2, 2, 2);
    if (k) {
	k->Fit(gapyfunction, "QR+");
	k->SetMinimum(0.6);
	k->SetMaximum(1.2);
    }

    k = (K4Stack*)gTalk->Draw(b->Similar("p1gapx"), 2, 2, 3);
    if (k) {
	k->Fit(mapx1function, "QR+");
	k->Fit(mapx2function, "QR+");
	k->SetMinimum(0.6);
	k->SetMaximum(1.2);
    }
    k = (K4Stack*)gTalk->Draw(b->Similar("p1gapy"), 2, 2, 4);
    if (k) {
	k->Fit(mapyfunction, "QR+");
	k->SetMinimum(0.6);
	k->SetMaximum(1.2);
    }

    gTalk->Draw("data 2006", 6, 6, 3, 1, kBlack);
    gTalk->Draw("data 2006", 6, 6, 6, 1, kBlack);
    gTalk->Draw("Monte Carlo", 6, 6, 21, .1, kBlack);
    gTalk->Draw("Monte Carlo", 6, 6, 24, 2, kBlack);
    gTalk->DrawLegend(5, 8, 12, 4);
    



    gTalk->Slide("wafer gaps correction effect");
    gTalk->Draw("data 2006", 6, 6, 3, 1, kBlack);
    gTalk->Draw("data 2006", 6, 6, 6, 1, kBlack);
    gTalk->Draw("Monte Carlo", 6, 6, 21, .1, kBlack);
    gTalk->Draw("Monte Carlo", 6, 6, 24, 2, kBlack);

    TObjArray*ecor = new TObjArray;
    ecor->Add(a->All("h1ee+all", 0, 0, 1));
    ecor->Add(a->All("h1eecor+all", 0, 0, 1));
    ecor->Add(b->All("h1ee+all", 0, 0, 1));
    ecor->Add(b->All("h1eecor+all", 0, 0, 1));
    gTalk->DrawK4StackArray(ecor, "HIST,E1");


    gTalk->Slide("electron selection");
    gTalk->Draw("data 2006", 6, 6, 3, 1, kBlack);
    gTalk->Draw("data 2006", 6, 6, 6, 1, kBlack);
    gTalk->Draw("Monte Carlo", 6, 6, 21, .1, kBlack);
    gTalk->Draw("Monte Carlo", 6, 6, 24, 2, kBlack);

    TObjArray*esel = new TObjArray;
    esel->Add(a->All("h1eecor+all", 0, 0, 1));
    esel->Add(a->All("h1eecor+electron", 0, 0, 1));
    esel->Add(b->All("h1eecor+all", 0, 0, 1));
    esel->Add(b->All("h1eecor+electron", 0, 0, 1));
    gTalk->DrawK4StackArray(esel, "HIST,E1");



    /*
    gTalk->Slide("y resolution");
    gTalk->Beauty(0.6);
    TMultiGraph*resolution = new TMultiGraph();
    resolution->Add(a->Resolution("h1deltaliny+standard", s1));
    resolution->Add(a->Resolution("h1deltalogy+standard", s2));
    //    resolution->Add(a->Resolution("x", "log+extended", s3));
    gTalk->Draw(resolution, 1, 1, 1, "ap");
    resolution->GetXaxis()->SetTitle("beam energy, GeV");
    resolution->GetYaxis()->SetTitle("y resolution, mm");
    gTalk->DrawLegend(4, 4, 7);

    a->Resolution(resolution);


    gTalk->Draw(s1, 4, 4, 4, "HIST,E1");
    gTalk->Draw(s2, 4, 4, 8, "HIST,E1");
    //    gTalk->Draw(s3, 3, 2, 6, "HIST,E1");
    */
    gTalk->Beauty(0.7, 0, 0);

            

    
    
    gTalk->Slide("track correlation");
    gTalk->Beauty(0.7, 0, 0);
    TObjArray*proba = new TObjArray();
    proba->Add(a->Sum("h2reflinx"));
    proba->Add(b->Sum("h2reflinx"));
    proba->Add(d->Sum("h2reflinx"));
    proba->Add(a->Sum("h2refliny"));
    proba->Add(b->Sum("h2refliny"));
    proba->Add(d->Sum("h2refliny"));

    gTalk->DrawTH1Array(proba, "col");
    
    gTalk->Draw("Data 2006", 3, 15, 1);
    gTalk->Draw("Monte Carlo",    3, 15, 2);
    gTalk->Draw("Monte Carlo + random.gaus(x_dc, 1 mm)",    3, 15, 3);
       


    gTalk->Slide("measurement");
    gTalk->Beauty(0.6);
    //    stax->Print();
    gTalk->DrawK4StackArray(stax, "HIST,E1");
    gTalk->Draw("Data 2006", 3, 15, 1);
    gTalk->Draw("Monte Carlo",    3, 15, 2);
    gTalk->Draw("Monte Carlo + random.gaus(x_dc, 1 mm)",    3, 15, 3);
    gTalk->DrawLegend(6, 3, 11, 3);


    //    gTalk->Slide("position resolution");
    gTalk->Slide();
    gTalk->Beauty(0.5);
    gTalk->Draw(xresolution, 2, 1, 1, "ap");
    xresolution->GetXaxis()->SetTitle("E, GeV");
    xresolution->GetYaxis()->SetTitle("x position resolution, mm");
    //    gTalk->DrawLegend(3, 4, 7, 3);

    gTalk->Draw(yresolution, 2, 1, 2, "ap");
    yresolution->GetXaxis()->SetTitle("E, GeV");
    yresolution->GetYaxis()->SetTitle("y position resolution, mm");
    gTalk->DrawLegend(3, 4, 9, 3);
    //    gTalk->PrintSlide("resox.eps");



    gTalk->Slide("summary & conclusions");
    gTalk->Draw("
The Si-W ECAL position resolution is NOT described by MC.;
The reason is NOT known yet.;
 ;
 ;
Account for the finite resolution of drift chambers by smearing hit position.;
 ;
1. Resolution as measured from data is reached at ~ 0.8 mm;
but drift chambers are expected to have better resolution.; 
 ;
2. The shape is different.;
 ;
-> The resolution of the drift chambers is not;
the (only) reason for the discrepancy;
 ;
 ;
Thanks for suggestions.;
", 1, 1, 1, 1, kBlack);




    gTalk->Slide();
    gTalk->Draw("APPENDIX");


    gTalk->Slide("Energy resolution");

    gTalk->Draw(eresolution, 1, 1, 1, "ap");
    gTalk->DrawLegend(3, 5, 6, 4);
    //    resolution->GetXaxis()->SetTitle("E^{-0.5} , GeV^{-0.5}");
    eresolution->GetXaxis()->SetTitle("E, GeV");
    eresolution->GetYaxis()->SetTitle("100#DeltaE/E, %");


    gTalk->Slide();
    gTalk->Beauty(0.5);
    gTalk->Draw(xxresolution, 2, 1, 1, "ap");
    xxresolution->GetXaxis()->SetTitle("E, GeV");
    xxresolution->GetYaxis()->SetTitle("x position resolution, mm");

    gTalk->Draw(yyresolution, 2, 1, 2, "ap");
    yyresolution->GetXaxis()->SetTitle("E, GeV");
    yyresolution->GetYaxis()->SetTitle("y position resolution, mm");
    gTalk->DrawLegend(3, 4, 9, 3);


    gTalk->Slide("Energy resolution fits");
    gTalk->Draw(" 
 FCN=19.8098 FROM MIGRAD    STATUS=CONVERGED     125 CALLS         126 TOTAL;
                     EDM=1.56568e-09    STRATEGY= 1      ERROR MATRIX ACCURATE; 
  EXT PARAMETER                                   STEP         FIRST   ;
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE ;
   1  stochastic term   1.75415e+01   1.75089e-01   1.79635e-04   4.40296e-04;
   2  constant term   1.34411e+00   8.30989e-02   8.52606e-05   3.02976e-04;
 FCN=20.5331 FROM MIGRAD    STATUS=CONVERGED      55 CALLS          56 TOTAL;
                     EDM=1.60969e-13    STRATEGY= 1      ERROR MATRIX ACCURATE ;
  EXT PARAMETER                                   STEP         FIRST   ;
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE ;
   1  stochastic term   1.78916e+01   2.86953e-01   2.93390e-04  -1.09676e-06;
   2  constant term   1.06027e+00   1.66300e-01   1.70023e-04   1.61443e-06;
", 1, 1, 1, 1, kBlack);

    gTalk->Slide("Position resolution fits");
    gTalk->Draw(" 
  EXT PARAMETER                                   STEP         FIRST   ;
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE ;
     1  MC+1.5 mm, stochastic term   2.72273e+00   6.69013e-01   2.97743e-04  -4.63676e-08;
     2  MC+1.5 mm, constant term   1.89385e+00   4.82803e-02   2.14868e-05   3.35487e-06;
  EXT PARAMETER                                   STEP         FIRST   ;
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE ;
     1  MC+1.0 mm, stochastic term   2.82332e+00   3.68079e-01   1.59769e-04  -6.00873e-07;
     2  MC+1.0 mm, constant term   1.34425e+00   3.70366e-02   1.60760e-05  -1.16887e-05;
  EXT PARAMETER                                   STEP         FIRST   ;
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE ;
     1  DATA, stochastic term   3.99324e+00   2.40932e-01   1.46730e-04  -1.07543e-05;
     2  DATA, constant term   1.01903e+00   3.95992e-02   2.41161e-05  -5.24213e-05;
  EXT PARAMETER                                   STEP         FIRST   ;
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE ;
     1  MC+0.5 mm, stochastic term   3.10440e+00   1.66791e-01   6.57173e-05  -4.33366e-05;
     2  MC+0.5 mm, constant term   7.17150e-01   2.96096e-02   1.16663e-05  -2.12919e-04;
  EXT PARAMETER                                   STEP         FIRST   ;
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE ;
     1  MC+0.0 mm, stochastic term   3.07511e+00   9.02601e-02   3.69390e-05  -1.27883e-04;
     2  MC+0.0 mm, constant term   2.42639e-01   4.09618e-02   1.67619e-05   8.76821e-04;
", 1, 1, 1, 1, kRed);



    /*
    gTalk->Slide("Angle resolution");
    resolution = new TMultiGraph();
    //    resolution->Add(a->Resolution("h1angle+electron", kTRUE, dummy, "DATA"));
    //    resolution->Add(b->Resolution("h1angle+electron", kTRUE, dummy, "MC"));
    resolution->Add(a->Resolution("h1angle+safe", kTRUE, dummy, "DATA/safe"));
    resolution->Add(b->Resolution("h1angle+safe", kTRUE, dummy, "MC/safe"));
    gTalk->Draw(resolution, 1, 1, 1, "ap");
    gTalk->DrawLegend(3, 5, 6, 4);
    //    resolution->GetXaxis()->SetTitle("E^{-0.5} , GeV^{-0.5}");
    resolution->GetXaxis()->SetTitle("E, GeV");
    resolution->GetYaxis()->SetTitle("angle resolution, mrad");
    K3Ana::Resolution(resolution, "Q");
    */

    /*
    gTalk->Slide("Shower dispersion");
    gTalk->Beauty(0.5, 0, 0);
    k = new K4Stack();
    k->Add(a->Sum("h1disperse+electron"));
    k->Add(b->Sum("h1disperse+electron"));
    k->NormalizeTo(1);
    gTalk->Draw(k, 1, 1, 1, "HIST,E1");
    gTalk->Draw("- data",                                    2, 15, 6, 0.1, kBlack);
    gTalk->Draw("- MC",                                      2, 15, 8, 0.1, kRed);
    gTalk->Draw("D = #sum_{i} d_{i} w_{i} / #sum_{i} w_{i}", 2, 15, 12, 0.1, kBlue);
    gTalk->Draw("d = distance of hit to shower axis",       2, 15, 14, 0.1, kBlue);
    */


//     gTalk->Logx();
//     gTalk->Logy();

 
//     gTalk->Slide("se");
//     gTalk->Draw(sedata, 2, 1, 1);
//     gTalk->Draw(semc, 2, 1, 2);

    

//    gTalk->Slide("gaus");
//    gTalk->Beauty(1.2);
    //    for (Int_t i = 0; i < nsta; ++i) gTalk->Draw(sta[i], 4, 3, i + 1, "HIST,E1");
    

    /*
    while (a->Loop()) {
	gTalk->Beauty(1.6, 0, 0);
 	gTalk->Slide(Form("Data at %s GeV", a->GetTitle()));
	gTalk->Draw(a->Similar("h3bclin", "Zlatka", "x"), 3, 3,  1,  "HIST,E1");
 	gTalk->Logy();
	gTalk->Draw(a->Similar("h3bclin", "Zlatka", "y"), 3, 3,  2,  "HIST,E1");
 	gTalk->Logy();
	gTalk->Draw(a->Similar("h3bclin", "Zlatka", "z"), 3, 3,  3,  "HIST,E1");
 	gTalk->Logy();
 	gTalk->Draw(a->Similar("h2track","x"),            3, 3,  4,  "HIST,E1");
 	gTalk->Logy();
 	gTalk->Draw(a->Similar("h2track","y"),            3, 3,  5,  "HIST,E1");
 	gTalk->Logy();
 	gTalk->Draw(a->Similar("h1deltalinx"),            3, 3,  7,  "HIST, E1");
 	gTalk->Logy();
 	gTalk->Draw(a->Similar("h1deltaliny"),            3, 3,  8,  "HIST, E1");
 	gTalk->Logy();
 	gTalk->Draw(a->Similar("h1disperse"),             3, 3,  9,  "HIST, E1");
	gTalk->Logy();
    }

    
    while (b->Loop()) {
	gTalk->Beauty(1.6, 0, 0);
 	gTalk->Slide(Form("Monte Carlo at %s GeV", b->GetTitle()));
	gTalk->Draw(b->Similar("h3bclin", "Zlatka", "x"), 3, 3,  1,  "HIST,E1");
 	gTalk->Logy();
	gTalk->Draw(b->Similar("h3bclin", "Zlatka", "y"), 3, 3,  2,  "HIST,E1");
 	gTalk->Logy();
	gTalk->Draw(b->Similar("h3bclin", "Zlatka", "z"), 3, 3,  3,  "HIST,E1");
 	gTalk->Logy();
 	gTalk->Draw(b->Similar("h2track","x"),            3, 3,  4,  "HIST,E1");
 	gTalk->Logy();
 	gTalk->Draw(b->Similar("h2track","y"),            3, 3,  5,  "HIST,E1");
 	gTalk->Logy();
 	gTalk->Draw(b->Similar("h1deltalinx"),            3, 3,  7,  "HIST, E1");
 	gTalk->Logy();
 	gTalk->Draw(b->Similar("h1deltaliny"),            3, 3,  8,  "HIST, E1");
 	gTalk->Logy();
 	gTalk->Draw(b->Similar("h1disperse"),             3, 3,  9,  "HIST, E1");
	gTalk->Logy();
    }
    */

    gTalk->SetTravail();
    gTalk->End();

//     delete canvas;
//     delete a;
//     delete b;
//     delete c;
//     delete d;
//     delete e;
//     delete f;
//     delete g;
    gSystem->Exit(0);
}
