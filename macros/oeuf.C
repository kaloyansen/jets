#include "TApplication.h"
#include "TArrayD.h"
#include "TCanvas.h"
#include "TDatime.h"
#include "TH3D.h"
#include "TMath.h"
#include "TRandom.h"
#include "TVector3.h"

int main(Int_t argc, char**argv) {
    TApplication application("oeuf", &argc, argv); 

    Int_t max = 11, MAX = max * max * max;
    Double_t isolation = TMath::Sqrt(max);
    Double_t weight = max * max;

    TArrayD a(MAX);
    TVector3*___r = new TVector3[MAX];

    TDatime datime;// = new TDatime();
    TRandom random(datime.Get());

    TCanvas c("oeuf", "oeuf", 1);
    c.SetFillColor(kBlack);
    TH3D h3("oeuf", "oeuf", max, -0.5, max - 0.5, max, -0.5, max - 0.5, max, -0.5, max - 0.5);
    h3.SetFillColor(kBlack);    

    Int_t i = 0;
    for (Int_t x = 0; x < max; ++x) 
	for (Int_t y = 0; y < max; ++y) 
	    for (Int_t z = 0; z < max; ++z) {
		a[i] = random.Gaus(weight);
		___r[i].SetXYZ(x, y, z);
		h3.Fill(x, y, z, a[i]);
		i++;
	    }


    TVector3 ___max, ___min, ___mindistance, ___maxdistance;
    Double_t maxval, minval, minmagnitude, maxmagnitude, magnitude;
    while (kTRUE) {
	___max.SetXYZ(-1, -1, -1);
	___min.SetXYZ(-1, -1, -1);
	maxval = 0;
	minval = 1e10;
	i = 0;
	while (i < MAX) {
	    ___max = (maxval > a[i]) ? ___max : ___r[i];
	    ___min = (minval < a[i]) ? ___min : ___r[i];
	    maxval = (maxval > a[i]) ? maxval : a[i];
	    minval = (minval < a[i]) ? minval : a[i];
	    //	    Info("", "%d %.0f %.0f %.0f %f", i, ___r[i].X(), ___r[i].Y(), ___r[i].Z(), a[i]);
	    i++;
	}
	i = 0;
	while (i < MAX) {
	    ___mindistance = ___min -  ___r[i];
	    ___maxdistance = ___max -  ___r[i];
	    minmagnitude = ___mindistance.Mag();
	    maxmagnitude = ___maxdistance.Mag();
	    //	    Info("magnitude", "%d %f", i, magnitude);
	    magnitude = (minmagnitude > maxmagnitude) ? minmagnitude : maxmagnitude;
	    if (magnitude  > isolation) {
		a[i] = random.Gaus(weight);
		h3.Fill(___r[i].X(), ___r[i].Y(), ___r[i].Z(), a[i]);
	    }
	    i++;
	}
	h3.Draw("ISO,FB,BB,COL");
	c.Update();
    }

    return 0;

}
