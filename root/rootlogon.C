{
 
gInterpreter->Info("rootlogon.C", "rootlogon.C");
gInterpreter->AddIncludePath("~/Myxa/mode/c++/src");
    //gInterpreter->AddIncludePath("../K4");
//gInterpreter->AddIncludePath("$H1DIST/releases/$H1CURRENT");
//biblioteki
gSystem->Load("libCore.so");
gSystem->Load("libGraf.so");
gSystem->Load("libPhysics.so");
//gSystem->Load("libSpectrum.so");
//gSystem->Load("libASImage.so");
gSystem->Load("libMatrix.so");
//gSystem->Load("libMinuit.so");
gSystem->Load("libPostscript.so");
gSystem->Load("libGraf3d.so");
gSystem->Load("libGeom.so");
gSystem->Load("libK3.so");

//scriptove
/*
gInterpreter->AddIncludePath("./named");
gInterpreter->Load("core.C");//always first 
//gInterpreter->Load("ana.C");
//gInterpreter->Load("fit.C");
gInterpreter->Load("pad.C");
gInterpreter->Load("r.C");
//gInterpreter->Load("hist.C");
//gInterpreter->Load("stack.C");
//gInterpreter->Load("multigraph.C");
gInterpreter->Load("trip.C");
*/

/*
TGaxis::SetMaxDigits(3);
TStyle*style=new TStyle("my","style");

style->SetPadBorderMode(0);//no shit b/w pads
style->SetTitleBorderSize(0);//no frame around the title
style->SetFrameFillColor(10);//color inside plots
style->SetTitleFillColor(10);//color around the main title

style->SetCanvasColor(0);//morla e mnogo hitra
style->SetFrameBorderMode(100);//za kakvo e tva - ne znam

style->SetStatBorderSize(0);//stat bez ramka 
style->SetStatColor(10);//stat bez fon
style->SetStatX(0.9);
style->SetStatY(0.89);
style->SetStatStyle(0);


// use method SetFillColor() 
// to change canvas color

gROOT->SetStyle("my");
*/


}
