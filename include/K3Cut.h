#ifndef __K3Cut__
#define __K3Cut__
#include <iostream>
#include <fstream>
#include "TNamed.h"

using namespace std;

class K3Cut : public TNamed {

    Bool_t fStat;
    Int_t fCount;
    Double_t fMin;
    Double_t fMax;

    void SetCount(Int_t count) { fCount = count; }
    void SetLimit(Double_t min, Double_t max) { fMin = min; fMax = max; }


public:
    K3Cut() : TNamed() {;}
    K3Cut(const char *name, Double_t min, Double_t max) : TNamed(name, "shit") { Reset(); SetLimit(min, max); }

    void SetStat(Bool_t stat = kTRUE) { fStat = stat; }
    void On() { SetStat(kTRUE); }
    void Off() { SetStat(kFALSE); }
    void Reset() { SetCount(0); Off(); }
    /*
    void Print(TString file = 0) {
	if (file) {
	    ofstream tout(file.Data(), "write");
	    tout<<GetName()<<"\t"<<Is()<<"\t"<<GetCount()<<"\t"<<GetMin()<<"\t"<<GetMax()<<"\n";
	    tout.close();
	    return;
	}
	cout<<GetName()<<"\t"<<Is()<<"\t"<<GetCount()<<"\t"<<GetMin()<<"\t"<<GetMax()<<endl;
    }
    */
    Bool_t Check(Double_t value);
    Bool_t Is() { return fStat; }
    Int_t Count();
    Int_t GetCount() { return fCount; }
    Double_t GetMin() { return fMin; }
    Double_t GetMax() { return fMax; }

    ClassDef(K3Cut,1); // Class to control cuts
};

#endif
