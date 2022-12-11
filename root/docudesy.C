{
    /*

    
  _ _ _  _ _ _.
 /     /     /|
/ _ _ / _ _ / |
|     |     | |
|   0 |   0 |/
- - - - - - '


    */

    gSystem->Load("libGeom.so");
    gSystem->Load("libGraf.so");
    gSystem->Load("libGraf3d.so");
    gSystem->Load("libHtml.so");
    gSystem->Load("libMatrix.so");
    gSystem->Load("libMinuit.so");
    gSystem->Load("libNet.so");
    gSystem->Load("libPhysics.so");
    gSystem->Load("libPostscript.so");
//    gSystem->Load("libRecorder.so");
    gSystem->Load("libSpectrum.so");
    gSystem->Load("libTree.so");


    //    gSystem->Load("libASImage.so");

    gSystem->Load("libK3.so");


    THtml*l = new THtml();
    //    TString inputDir="../src";
    //    inputDir+=":/home/kaloyan/svn/rootsource";
    TString inputDir = "/afs/desy.de/user/k/kaloyan/Myxa/mode/c++/src";
    l->SetSourceDir(inputDir.Data());
    l->SetOutputDir("$(HOME)/www/root");
    l->SetAuthorTag("Kaloyan Kratsev");
    l->SetRootURL("http://root.cern.ch/root/html");
    l->SetEscape(255);
    l->MakeAll();
    l->MakeIndex();
    delete l;

    gSystem->Exit(0);
}

