{
    TString fileName = "~/data/control.root";

    TFile f(fileName);
    K3Control*c[7];
    f.GetObject("test6", c[0]);
    f.GetObject("test8", c[1]);
    f.GetObject("test10", c[2]);
    f.GetObject("test15", c[3]);
    f.GetObject("test20", c[4]);
    f.GetObject("test30", c[5]);
    f.GetObject("test45", c[6]);
    f.Close();

    gSystem->Exit(0);
}
