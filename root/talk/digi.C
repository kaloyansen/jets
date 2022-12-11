{
     K3Ana * a = new K3Ana();
     a->GetFile("data/kaloyan_all_300672.root");
     a->GetFile("data/kaloyan_300672.mc.no.noise.root");
     a->GetFile("data/kaloyan_300672.mc.with.noise.root");
     K3Control cData = a->fC[0];
     K3Control cMCnn = a->fC[1];
     K3Control cMC = a->fC[2];

     gROOT->SetBatch();
     K4Talk::Style();
     TCanvas * canvas = new TCanvas("Kaloyan Krastev, LPSC Grenoble", "CALICE Analysis", 1920, 1080);
//     TCanvas * canvas = new TCanvas("Kaloyan Krastev, LPSC Grenoble", "CALICE Analysis", 2100, 1400);
     K4Talk::Instance("digi.pdf", canvas);
     gTalk->Inverse();
//     gTalk->SetPrint();
     gTalk->Slide("ECAL Digitization Status");

     K4Stack * st;

     gTalk->Slide("ECAL reconstruction");
     gTalk->Draw("~/Myxa/mode/c++/root/slides/simrec.slide");


     // gTalk->Slide("event energy 2");
     // K4Stack * energyStack1 = new K4Stack(cMC->FamilyList("energymip"));
     // energyStack1->Add(cMCnn->FamilyList("energymip"));
     // energyStack1->Normalize();
     // gTalk->Draw(energyStack1, 1, 1, 1, "hist, e");
     // gTalk->Logy();

     // gTalk->DrawLegend(3, 2, 2, 3);


     // gTalk->Slide("event muliplicity");
     // K4Stack * energyStack2 = new K4Stack(cData->FamilyList("mulall"));
     // energyStack2->Add(cMC->FamilyList("mulall"));
     // energyStack2->Normalize();
     // gTalk->Draw(energyStack2, 1, 1, 1, "hist, e");
     // gTalk->Logy();

     // gTalk->DrawLegend(3, 2, 3, 3);

     // gTalk->Slide("event multiplicity 2");
     // K4Stack * energyStack3 = new K4Stack(cMC->FamilyList("mulall"));
     // energyStack3->Add(cMCnn->FamilyList("mulall"));
     // energyStack3->Normalize();
     // gTalk->Draw(energyStack3, 1, 1, 1, "hist, e");
     // gTalk->Logy();

     // gTalk->DrawLegend(3, 2, 3, 3);



     // gTalk->Slide("event multiplicity 4");
     // K4Stack * energyStack3 = new K4Stack(cMC->FamilyList("mulcut"));
     // energyStack3->Add(cMCnn->FamilyList("mulcut"));
     // energyStack3->Normalize();
     // gTalk->Draw(energyStack3, 1, 1, 1, "hist, e");
     // gTalk->Logy();

     // gTalk->DrawLegend(3, 2, 3, 3);


     // gTalk->Draw(gTalk->StackFromList(cData->FamilyList("energymip")), 2, 2, 1, "hist, e");
     // gTalk->DrawLegend(4, 3, 4, 2);
     // gTalk->Draw(gTalk->StackFromList(cData->FamilyList("mulall")), 2, 2, 2, "hist, e");
     // gTalk->DrawLegend(4, 3, 4, 2);
     // gTalk->Draw(gTalk->StackFromList(cMC->FamilyList("energymip")), 2, 2, 3, "hist, e");
     // gTalk->DrawLegend(4, 3, 4, 2);
     // gTalk->Draw(gTalk->StackFromList(cMC->FamilyList("mulall")), 2, 2, 4, "hist, e");

     // gTalk->Slide("Data");
     // gTalk->DrawList(cData->FamilyList("layer"), "col");
     // gTalk->Draw(gTalk->StackFromList(cData->FamilyList("energymip")), 3, 2, 2, "hist, e");
     // gTalk->Draw(gTalk->StackFromList(cData->FamilyList("mulall")), 3, 2, 3, "hist, e");
     // gTalk->DrawLegend(4, 3, 4, 2);

     // gTalk->Slide("MC");
     // gTalk->DrawList(cMC->FamilyList("layer"), "col");
     // gTalk->Draw(gTalk->StackFromList(cMC->FamilyList("energymip")), 3, 2, 2, "hist, e");
     // gTalk->Draw(gTalk->StackFromList(cMC->FamilyList("mulall")), 3, 2, 3, "hist, e");
     // gTalk->DrawLegend(4, 3, 4, 2);


     // gTalk->Slide("Data energy fraction by layer");
     // gTalk->DrawList(cData->FamilyList("frac"), "col");


/*

     gTalk->Slide("Simulated Monte Carlo");
     gTalk->DrawLayers(cMC->Identify("map+34"), "col");

     gTalk->Slide("Reconstructed data");
     gTalk->DrawLayers(cData->Identify("map+22"), "col");

     gTalk->Slide("Digitized Monte Carlo");
     gTalk->DrawLayers(cMCnn->Identify("map+18"), "col");

     gTalk->Slide("Digitized Monte Carlo with noise");
     gTalk->DrawLayers(cMC->Identify("map+18"), "col");

     cMCnn->Glist("map", 1);
     cMC->Glist("map", 1);
*/

     for (Int_t i = 1; i <= 30; ++i) 
	  if (i == 6 || i == 26) {
	       gTalk->Slide(Form("Layer %d", i));
	       gTalk->DrawLayer(i, cMCnn->Identify("map+34"), 3, 2, 1, "col");
	       gTalk->DrawLayer(i, cMCnn->Identify("map+18"), 3, 2, 2, "col");
	       gTalk->DrawLayer(i, cMC->Identify("map+18"),   3, 2, 3, "col");
	       gTalk->DrawLayer(i, cData->Identify("map+22"), 3, 2, 6, "col");

	       gTalk->Draw("      MC(sim)", 3, 4, 4, 1, kRed);
	       gTalk->Draw("      MC(rec)", 3, 4, 5, 1, kRed);
	       gTalk->Draw("    MC(noise)", 3, 4, 6, 1, kRed);
	       gTalk->Draw("         data", 3, 4, 12);
	  }
     


     gTalk->Slide("event energy");
     st = new K4Stack(cData->FamilyList("energymip"));
     st->Add(cMC->FamilyList("energymip"));
     st->Normalize();
     gTalk->Draw(st, 1, 1, 1, "hist, e");
     gTalk->DrawLegend(3, 2, 3, 3);

     gTalk->Slide("hit muliplicity");
     st = new K4Stack(cData->FamilyList("mulcut"));
     st->Add(cMC->FamilyList("mulcut"));
     st->Normalize();
     gTalk->Draw(st, 1, 1, 1, "hist, e");
     gTalk->DrawLegend(3, 2, 3, 3);


     gTalk->Slide("Event energy reconstruction");
     
     st = (K4Stack *)gTalk->Draw(gTalk->StackFromList(cMCnn->FamilyList("energymip")), 2, 2, 1, "hist, e"); st->Normalize();
     st = (K4Stack *)gTalk->Draw(gTalk->StackFromList(cMC->FamilyList("energymip")), 2, 2, 2, "hist, e");// st->Normalize();
     gTalk->DrawLegend(4, 5, 4, 4);
     gTalk->Draw(cMCnn->Identify("effevent+00"), 2, 2, 3, "col");
     gTalk->Draw(cMC->Identify("effevent+00"), 2, 2, 4, "col");
     gTalk->Draw("w/o noise", 6, 2, 2);
     gTalk->Draw("w/ noise", 6, 2, 5);


     gTalk->Slide("Hit energy reconstruction");
     st = (K4Stack *) gTalk->Draw(gTalk->StackFromList(cMCnn->FamilyList("hitmip")), 2, 2, 1, "hist, e");// st->Normalize();
     st = (K4Stack *) gTalk->Draw(gTalk->StackFromList(cMC->FamilyList("hitmip")), 2, 2, 2, "hist, e");// st->Normalize();
     gTalk->DrawLegend(4, 5, 4, 4);
     gTalk->Draw(cMCnn->Identify("effhit+16"), 2, 2, 3, "col");
     gTalk->Draw(cMC->Identify("effhit+16"), 2, 2, 4, "col");
     gTalk->Draw("w/o noise", 6, 2, 3);
     gTalk->Draw("w/ noise", 6, 2, 6);


/*
     gTalk->Slide("hit multiplicity");
     gTalk->Draw(cData->Identify("layer+20"), 2, 2, 1, "col");
     gTalk->Draw(cMC->Identify("layer+32"), 2, 2, 2, "col");
     gTalk->Draw(cMCnn->Identify("layer+16"), 2, 2, 3, "col");
     gTalk->Draw(cMC->Identify("layer+16"), 2, 2, 4, "col");
*/


//     gTalk->DrawList(cData->FamilyList("frac"), "col");

     // gTalk->Draw(a->All("mulall+24"), 2, 2, 2);
     // gTalk->Draw(a->All("mulcut+24"), 2, 2, 3);
     // gTalk->Draw(a->All("energymip+24"), 2, 2, 4);


/*
     gTalk->Slide("Noise Parameters Upload");
     for (int i = 0; i < 30; ++i) {
	  TString name = Form("p_noise_%d", i);
	  gTalk->DrawObjectFromFile(name, "data/upload_all_300672.root", 6, 5, i + 1, "", kFALSE);
     }
     gTalk->Slide("Noise Parameters Download");
     for (int i = 0; i < 30; ++i) {
	  TString name = Form("p_noise_%d", i);
	  gTalk->DrawObjectFromFile(name, "data/download_300672.root", 6, 5, i + 1, "", kFALSE);
     }
*/


     gTalk->Slide("ECAL reconstructed to simulated hit relation");
     gTalk->Draw("~/Myxa/mode/c++/root/slides/relation.slide");

     gTalk->Slide("Conclusions");
     gTalk->Draw("
;
Reconstructed hit is linked to the simulated (implemented in the calibration processor as LCRelation collection);
Warning: duplicates sim/rec hits;
Question 1: Do we drop the original collections?;
Question 2: Do we introduce fake sim hits in data to be consistent?;
;
Noise is now added by the digi processor (minor changes in TBEcalDigi required);
ECAL imperfection is transfered to Monte Carlo; 
The impact on event energy and hit multiplicity is negligible;
Noise upload during future mass production is strongly recommended;
;
Warning: Reconstructed hit energy loss;
Question 1: Could we recommend digitized Monte Carlo production in future?;
Question 2: Are there more studies needed?;
;  
", 1, 1, 1);
     
     

     for (int i = 0; i < 30; ++i) {
	  TString name = Form("p_noise_%d", i);
	  TString title = Form("Noise (ECAL Layer %.2d)", i + 1);
	  gTalk->Slide(title);
	  gTalk->DrawObjectFromFile(name, "data/upload_all_300672.root", 1, 2, 1);
	  gTalk->DrawObjectFromFile(name, "data/download_300672.root", 1, 2, 2);
	  gTalk->Draw("uploaded", 3, 2, 2, 1, kBlue);
	  gTalk->Draw("downloaded", 3, 2, 5, 1, kRed);
     }



     gTalk->SetTravail();
     gTalk->End();
    

     delete canvas;
     gSystem->Exit(0);
}
