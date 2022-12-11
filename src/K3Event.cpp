#include "K3Event.h"

ClassImp(K3Event);



void K3Event::FillBunch(Int_t BunchType,Float_t P_current,Float_t P_p_current)
{
    h1BunchType=BunchType;
    h1P_current=P_current;
    h1P_p_current=P_p_current;
}

void K3Event::FillVertex(Float_t VtxX,Float_t VtxY,Float_t VtxZ)
{
    h1VtxX=VtxX;
    h1VtxY=VtxY;
    h1VtxZ=VtxZ;
}

void K3Event::FillH1Gen(Float_t&Q2eGen,Float_t&YhGen,Float_t&ElecEGen,Float_t&Weight1,Float_t&Weight2) { 
    h1Q2e=Q2eGen; 
    h1Yh=YhGen; 
    h1ElecE=ElecEGen; 
    h1Weight1=Weight1;
    h1Weight2=Weight2;
}


void K3Event::FillH1(Short_t&Ivtyp,
		     Short_t&NumCentralTracks,
		     Short_t&NumEmParts,
		     Short_t&NumHfs,
		     Short_t&NumKtJets,
		     Int_t&EventNumber,
		     Int_t&Ibg,
		     Int_t&Ibgfm,
		     Int_t&L4dec,
		     Int_t&RunNumber,
		     Float_t&ElecE,
		     Float_t&ElecTheta,
		     Float_t&Epz,
		     Float_t&Etag6,
		     Float_t&KtJetPt, 
		     Float_t&KtJetTheta,
		     Float_t&Pt2HatGki,  
		     Float_t&PtMiss,
		     Float_t&Q2e,
		     Float_t&Q2h,
		     Float_t&ScalEt,
		     Float_t&T0_CJC,
		     Float_t&T0_LAr,
		     Float_t&Weight1,
		     Float_t&Weight2,
		     Float_t&Ye,
		     Float_t&Yh)
{
    h1Ivtyp=Ivtyp;
    h1NumCentralTracks=NumCentralTracks;
    h1NumEmParts=NumEmParts;
    h1NumHfs=NumHfs;
    h1NumKtJets=NumKtJets;

    h1EventNumber=EventNumber;
    h1Ibg=Ibg;    
    h1Ibgfm=Ibgfm;    
    h1L4dec=L4dec;    
    h1RunNumber=RunNumber;

    h1ElecE=ElecE;
    h1ElecTheta=ElecTheta;
    h1Epz=Epz;
    h1Etag6=Etag6;
    h1KtJetPt=KtJetPt;
    h1KtJetTheta=KtJetTheta;
    h1Pt2HatGki=Pt2HatGki;  
    h1PtMiss=PtMiss;
    h1Q2e=Q2e;
    h1Q2h=Q2h;
    h1ScalEt=ScalEt;
    h1T0_CJC=T0_CJC;
    h1T0_LAr=T0_LAr;
    h1Ye=Ye;
    h1Yh=Yh;
    h1Weight1=Weight1;
    h1Weight2=Weight2;
}




K3Jet*K3Event::AddJet(TLorentzVector jet4vec,Float_t z,Bool_t isGamma)
{//jet adder
    TClonesArray&jets=*fJets;
    K3Jet*jet = new(jets[fJetsIndex++]) K3Jet(jet4vec,z,isGamma);
    return jet;
}


K3Trigger*K3Event::AddTrigger(Byte_t l1te,Byte_t l2te,Byte_t l1rw,Byte_t l1ac,Byte_t l1l2rw,Byte_t l1l3rw,Byte_t l1l2l3ac,Byte_t l4vst,Byte_t Trigac,Byte_t l4class)
{//trigger adder
    TClonesArray&triggers=*fTriggers;
    K3Trigger*trigger = new(triggers[fTriggersIndex++]) K3Trigger(l1te,l2te,l1rw,l1ac,l1l2rw,l1l3rw,l1l2l3ac,l4vst,Trigac,l4class);
    return trigger;    
}

K3Trigger*K3Event::Trigger(Int_t n)
{//trigger getter
    K3Trigger*trigger=(K3Trigger*)fTriggers->At(n);
    return trigger;
}

Int_t K3Event::TE(Int_t sub,Int_t num)
{//this retuns subtrigger value
    Int_t value=0;
    for (Int_t i=0;i<num;++i) {
	Int_t te=Trigger(sub+i)->l1te;
	value+=te*(Int_t)pow(2.0,i);
    }
    return value;
}


void K3Event::Shift(Float_t shift)
{
    
    for (Int_t j=0;j<fJetsIndex;++j) {
	K3Jet*jet=this->Jet(j);
	TLorentzVector fourvec=jet->h1Hadron;
	jet->h1Hadron=fourvec*shift;
    }

    TLorentzVector fourvec=this->h1Hadron;
    this->h1Hadron=fourvec*shift;

}

void K3Event::BeautifulJets(Float_t etaMin1,Float_t etaMax1,
			    Float_t etaMin2,Float_t etaMax2,
			    Float_t etaMin3,Float_t etaMax3,
			    Float_t etaMin4,Float_t etaMax4,
			    Float_t etMin1,Float_t etMin2,
			    Float_t etMin3,Float_t etMin4,
			    TObjArray*array,Float_t shift)
{
    if (shift!=1.) Shift(shift);

    Float_t etMin[fJetsIndex];
    Float_t etaMin[fJetsIndex];
    Float_t etaMax[fJetsIndex];

    for (Int_t j=0;j<fJetsIndex;++j) { 
	etMin[j]=etMin4;
	etaMin[j]=etaMin4;
	etaMax[j]=etaMax4;
    }

    etMin[0]=etMin1; 
    etaMin[0]=etaMin1;
    etaMax[0]=etaMax1;

    etMin[1]=etMin2; 
    etaMin[1]=etaMin2;
    etaMax[1]=etaMax2;

    etMin[2]=etMin3; 
    etaMin[2]=etaMin3;
    etaMax[2]=etaMax3;

    etMin[3]=etMin4; 
    etaMin[3]=etaMin4;
    etaMax[3]=etaMax4;

    array->Clear();
    Int_t cut=0;
    Float_t currentEt=10000000,et,eta;
    for (Int_t j=0;j<fJetsIndex;++j) {
	et=Et(j);
	eta=Eta(j);
	if (et>currentEt) Warning("BeautifulJets","Wrong Et_jet ordering");
	currentEt=et;//proverka za podredbata
	if (eta>etaMin[cut]&&eta<etaMax[cut]&&et>etMin[cut]) {
	    array->Add(Jet(j));
	    cut++;
	} else return;
    }
}


Float_t K3Event::Et(Int_t n)
{
    K3Jet*j=Jet(n);
    Float_t et=0;
    if (j) et=j->h1Hadron.Et();
    return et;
}

Float_t K3Event::Eta(Int_t n)
{
    K3Jet*j=Jet(n);
    Float_t eta=0;
    if (j) eta=j->h1Hadron.Eta();
    return eta;
}

K3Jet*K3Event::Jet(Int_t n)
{//jet getter
    if (n<fJetsIndex) {    
	K3Jet*jet=(K3Jet*)fJets->At(n);
	return jet;
    } 
    return 0;
}

