{
    /*

    
  _ _ _  _ _ _.
 /     /     /|
/ _ _ / _ _ / |
|     |     | |
|   0 |   0 |/
- - - - - - '


    */

    /*
    gSystem->Load("libASImage.so");
    //    gSystem->Load("libGeom.so");
    gSystem->Load("libGraf.so");
    gSystem->Load("libGraf3d.so");
    gSystem->Load("libHistPainter.so");
    gSystem->Load("libHtml.so");
    gSystem->Load("libMatrix.so");
    gSystem->Load("libMinuit.so");
    gSystem->Load("libNet.so");
    gSystem->Load("libPhysics.so");
    gSystem->Load("libPostscript.so");
    gSystem->Load("libRecorder.so");
    //    gSystem->Load("libRooFit.so");
    gSystem->Load("libSpectrum.so");
    gSystem->Load("libSPlot.so");
    gSystem->Load("libSQL.so");
    gSystem->Load("libTree.so");


    //    gSystem->Load("libASImage.so");


    */
    //    gSystem->Load("libK3.so");
    

    THtml*l = new THtml();
    //    l->LoadAllLibs();
    l->SetProductName("K3");
    //    TString inputDir = "/home/kkrastev/Myxa/mode:/home/kkrastev/soft/root_trunk";
    //    l->SetInputDir(inputDir.Data());
    l->SetOutputDir("$(HOME)/public_html/root");
    l->SetAuthorTag("Kaloyan Kratsev");
    l->SetRootURL("http://root.cern.ch/root/html");
    l->SetEscape(255);
    l->MakeAll();
    l->MakeIndex();
    delete l;

    gSystem->Exit(0);
}

