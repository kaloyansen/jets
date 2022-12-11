#include "K3Jet.h"

ClassImp(K3Jet);


K3Jet::K3Jet(K3Jet*j)
{
    h1Hadron=j->h1Hadron;
    fFloat=j->GetFloat();
    fBool=j->GetBool();
    //    fMatchedJet=j->Matched();
}

K3Jet::K3Jet(Float_t px,Float_t py,Float_t pz,Float_t e,Float_t f,Bool_t b)
{
    //    fMatchedJet=0;
    h1Hadron.SetPxPyPzE(px,py,pz,e);
    fFloat=f;
    fBool=b;
    //    for (Int_t b=0;b<11;++b) fPsi[b]=0;
    //    h1Hadron=h1partjet->GetFourVector();
}

K3Jet::K3Jet(TLorentzVector jet4vector,Float_t f,Bool_t b)
{
    //    fMatchedJet=0;
    h1Hadron=jet4vector;
    fFloat=f;
    fBool=b;
    //    for (Int_t b=0;b<11;++b) fPsi[b]=0;
    //    h1Hadron=h1partjet->GetFourVector();

    /*
    Float_t r,rMax,p,jetPt,j;
    r=rMax=p=jetPt=j=0;
    
    for (Int_t i=0;i<h1partjet->GetNumOfParticles();++i) {
	H1PartCand*part=(H1PartCand*)h1partjet->GetParticle(i);
        r=Angle(h1partjet,part);
	p=part->GetPt();
	jetPt=h1partjet->GetPt();
	j+=p;
	if (r<=0.1) fPsi[0]+=p; 
	if (r<=0.2) fPsi[1]+=p; 
	if (r<=0.3) fPsi[2]+=p; 
	if (r<=0.4) fPsi[3]+=p; 
	if (r<=0.5) fPsi[4]+=p; 
	if (r<=0.6) fPsi[5]+=p; 
	if (r<=0.7) fPsi[6]+=p; 
	if (r<=0.8) fPsi[7]+=p; 
	if (r<=0.9) fPsi[8]+=p; 
	if (r<=1.0) fPsi[9]+=p; 
	fPsi[10]+=p;

    }

    for (Int_t bin=0;bin<11;++bin) {
	fPsi[bin]/=j;
    }
    */
}


/*
Float_t K3Jet::Angle(H1Part*a,H1Part*b)
{//lorenz-invariant angle between two particles
  Float_t deta = a->GetEta() - b->GetEta();
  Float_t dphi = H1PartJet::GetRealPhi(a->GetPhi() - b->GetPhi());
  Float_t r = TMath::Sqrt(deta * deta + dphi * dphi);
  return r;
}
*/













