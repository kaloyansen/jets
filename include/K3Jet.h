#ifndef __K3Jet__
#define __K3Jet__
#include "TLorentzVector.h"

class K3Jet: public TObject {
    Bool_t fBool;
    Float_t fFloat;
    //    K3Jet*fMatchedJet; needs destructor
    //    Float_t fPsi[11];

public:
    K3Jet() { h1Hadron.SetPxPyPzE(0,0,0,0); }
    K3Jet(TLorentzVector,Float_t f=0,Bool_t b=kFALSE);
    K3Jet(Float_t px,Float_t py,Float_t pz,Float_t e,Float_t f=0,Bool_t b=kFALSE);
    K3Jet(K3Jet*);

    //    void Match(K3Jet v) { fMatchedJet=&v; }
    //    K3Jet*Matched() { return fMatchedJet; }

    TLorentzVector h1Hadron;


    Bool_t GetBool() { return fBool; }
    Float_t GetFloat() { return fFloat; }
    void SetBool(Bool_t b) { fBool=b; }
    void SetFloat(Float_t f) { fFloat=f; }
    void Show() {Info("Show","%f %f",h1Hadron.Et(),h1Hadron.Eta());}
    //    Float_t Angle(H1Part*a,H1Part*b);

    inline void PrintBits(Int_t dec,Int_t max=30) {
	for (Int_t i=max;i>=0;i--) {
	    Int_t bit=((dec>>i)&1);
	    Error("","%d->%d",i,bit);
	}
	//	cout<<endl;
    }

    ClassDef(K3Jet,4); // Base class for jet info
};

#endif
