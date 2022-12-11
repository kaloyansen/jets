#ifndef __K3Event__
#define __K3Event__
#include "TClonesArray.h"
#include "TUnixSystem.h"
#include "K3Jet.h"
#include "K3Trigger.h"

class K3Event: public K3Jet {

    TClonesArray*fTriggers;   //->
    TClonesArray*fJets;      //->
    Int_t fJetsIndex,fTriggersIndex;
    void Shift(Float_t shift);

public:

    K3Event() {
	fJets=new TClonesArray("K3Jet",0);
	fTriggers=new TClonesArray("K3Trigger",0);
	this->Clear();
    }

    TLorentzVector h1Electron;
    Short_t h1Ivtyp,h1NumCentralTracks,h1NumEmParts,h1NumHfs,h1NumKtJets;
    Int_t h1EventNumber,h1Ibg,h1Ibgfm,h1L4dec,h1RunNumber,h1BunchType;
   
    Float_t h1ElecE,h1ElecTheta,h1Epz,h1Etag6,h1KtJetPt,h1KtJetTheta;
    Float_t h1Pt2HatGki,h1PtMiss,h1Q2e,h1Q2h,h1ScalEt,h1T0_CJC,h1T0_LAr;
    Float_t h1Weight1,h1Weight2,h1Ye,h1Yh,h1P_current,h1P_p_current;
    Float_t h1VtxX,h1VtxY,h1VtxZ,h1Charge;

    void BeautifulJets(Float_t,Float_t,Float_t,Float_t,
		       Float_t,Float_t,Float_t,Float_t,
		       Float_t,Float_t,Float_t,Float_t,
		       TObjArray*,Float_t shift=1);
    void FillVertex(Float_t,Float_t,Float_t);
    void FillBunch(Int_t,Float_t,Float_t);
    void FillH1Gen(Float_t&,Float_t&,Float_t&,Float_t&,Float_t&);
    void FillH1(Short_t&,Short_t&,Short_t&,Short_t&,Short_t&,
		Int_t&,Int_t&,Int_t&,Int_t&,Int_t&,
		Float_t&,Float_t&,Float_t&,Float_t&,Float_t&,
		Float_t&,Float_t&,Float_t&,Float_t&,
		Float_t&,Float_t&,Float_t&,Float_t&,
		Float_t&,Float_t&,Float_t&,Float_t&);
    void Clear() {
	fJets->Clear("C");
	fJetsIndex=0;
	fTriggers->Clear("C");
	fTriggersIndex=0;
	h1Hadron.SetPxPyPzE(0,0,0,0);
	h1Electron.SetPxPyPzE(0,0,0,0);
	h1Ivtyp=h1NumCentralTracks=h1NumEmParts=h1NumHfs=h1NumKtJets=0;
	h1EventNumber=h1Ibg=h1Ibgfm=h1L4dec=h1RunNumber=h1BunchType=0;
	h1ElecE=h1ElecTheta=h1Epz=h1Etag6=h1KtJetPt=h1KtJetTheta=0;
	h1Pt2HatGki=h1PtMiss=h1Q2e=h1Q2h=h1ScalEt=h1T0_CJC=h1T0_LAr=0;
	h1Weight1=h1Weight2=1;
	h1Ye=h1Yh=h1P_current=h1P_p_current=0;
	h1VtxX=h1VtxY=h1VtxZ=h1Charge=0;
	SetFloat(0);
	SetBool(kFALSE);
    }

    Int_t TE(Int_t sub=0,Int_t num=1);
    Float_t Et(Int_t);    
    Float_t Eta(Int_t); 

    K3Trigger*AddTrigger(Byte_t,Byte_t,Byte_t,Byte_t,Byte_t,Byte_t,Byte_t,Byte_t,Byte_t,Byte_t);
    K3Trigger*Trigger(Int_t);
    K3Jet*AddJet(TLorentzVector jet4vec,Float_t z,Bool_t isGamma);
    K3Jet*Jet(Int_t);

    ClassDef(K3Event,4); // K3 Event class
};

#endif
