#include "K3Space.h"
ClassImp(K3Space);

K3Space::K3Space() { fArray= 0; fCorrelationMatrix = 0; fIndex = 0;} 
K3Space::~K3Space() { 
     if (fArray) {
	  fArray->Clear("C");
	  delete fArray; 
     }	
     if (fCorrelationMatrix) delete fCorrelationMatrix; 
}


K3Cut*K3Space::Add(TString name, Double_t min, Double_t max) 
{
     if (!fArray) {
	  fArray = new TClonesArray("K3Cut"); 
	  fArray->SetOwner();
     }

     TClonesArray & array = *fArray;
     fIndex = fArray->GetEntries();
     K3Cut * cut = new(array[fIndex++]) K3Cut(name, min, max);
     return cut;
}

K3Cut*K3Space::Get(TString name) 
{
     K3Cut * cut = 0;
     if (!fArray) { Warning("Get", "empty space"); return cut; }
     cut = (K3Cut*)fArray->FindObject(name);
     if (!cut) Error("Get", "<%s> not found", name.Data());
     return cut;
}

TString * K3Space::Names()
{
     TString * names = new TString[fIndex];
     for (Int_t i = 0; i < fIndex; ++i) { 
	  K3Cut * cut = (K3Cut *)fArray->At(i);
	  names[i] = cut->GetName();
     }
     return names;
}

void K3Space::State()
{
     Info("State", "current state:");
     Info("State", Form("%d cuts, status %d", fIndex, this->Encode()));
     this->Print();
}

Int_t K3Space::Encode()
{
     Double_t code = 0;
     for (Int_t i = 0; i < fIndex; ++i) { 
	  K3Cut * cut = (K3Cut *)fArray->At(i);
	  if (cut->Is()) code += pow(2, i); 
     }

     return Int_t(code);
}


void K3Space::Print()
{
     TString * name = Names();
     for (Int_t i = 0; i < fIndex; i++) 
	  Info("", Form("%d %s", i, name[i].Data()));

     delete [] name;

     if (!fCorrelationMatrix) {
	  Info("Print", "empty correlation matrix, FillCorrelationMatrix(Float_t weight) method used by K3Control Fill() method");
	  return;
     }

/*
     Int_t matrixindex = 0;
     for (Int_t i = 0; i < fIndex; ++i) {  
	  Info("Print", Form("%d", i));
	  for (Int_t j = 0; j < fIndex; ++j)  { 
	       if (i >= j) {
		    Info("Print", Form("%d", j));
		    Info("Print", Form("%f", fCorrelationMatrix->At(matrixindex)));
	       }
	       matrixindex++;
	  }
	  Info("Print", "end");
     }
*/
}





TString K3Space::Decode(Int_t code)
{
     TString * name = Names();
     TString decoded = "";
     for (Int_t i = 0; i < fIndex; i++) {
	  Bool_t  bit = ((code >> i) & 1);
	  if (bit) decoded += Form("%s+", name[i].Data());
     }

     delete [] name;
     return decoded;
}

void K3Space::Set(TString name, Bool_t what)
{
     K3Cut * cut = this->Get(name);
     if (!cut) return;
     cut->SetStat(what);
}

void K3Space::Off(TString name)
{
     if (name.CompareTo("switch_off_all")) {
	  K3Cut * cut = this->Get(name);
	  if (cut) cut->Off();
     } else {
	  for (Int_t i = 0; i < fIndex; ++i) { 
	       K3Cut * cut = (K3Cut *)fArray->At(i);
	       cut->Off();
	  }
     }
}


void K3Space::On(TString name)
{
     if (name.CompareTo("switch_on_all")) {
	  K3Cut * cut = this->Get(name);
	  if (cut) cut->On();
     } else {
	  for (Int_t i = 0; i < fIndex; ++i) { 
	       K3Cut * cut=(K3Cut *)fArray->At(i);
	       cut->On();
	  }
     }
}



Bool_t K3Space::Check(TString name, Double_t value) 
{ 
     K3Cut*cut = this->Get(name);
     if (cut) return cut->Check(value);
     return kFALSE;
}

Bool_t K3Space::Is(TString name) 
{ 
     K3Cut * cut = this->Get(name);
     if (cut) return cut->Is();
     return kFALSE;
}

Int_t K3Space::Count(TString name) 
{ 
     K3Cut * cut = this->Get(name);
     if (cut) return cut->Count();
     return 0;
}


void K3Space::FillCorrelationMatrix(Double_t width)
{
     if (!fCorrelationMatrix) fCorrelationMatrix = new TArrayD(1000);
     for (Int_t i = 0; i < fIndex; ++i) { 
	  K3Cut * cut_i = (K3Cut*)fArray->At(i);
	  for (Int_t j = 0; j < fIndex; ++j) { 
	       K3Cut * cut_j = (K3Cut*)fArray->At(j);
	       Int_t matrixindex = i * fIndex + j;
	       if (cut_i->Is() && cut_j->Is()) fCorrelationMatrix->AddAt(fCorrelationMatrix->At(matrixindex) + width, matrixindex);		
	  }
     }
}



TH2D*K3Space::CorrelationMatrixHistogram() 
{
     TH2D * h2 = 0;
     h2 = new TH2D("k3cut", "k3cut", fIndex, 0, 1, fIndex, 0, 1); 
     h2->SetBit(TH1::kCanRebin);
     h2->SetStats(0);
     TString * name = Names(); 
     for (Int_t i = 0; i < fIndex; ++i) 
	  for (Int_t j = 0; j < fIndex; ++j)   
	       if (i >= j) 
		    h2->Fill(name[i], name[j], fCorrelationMatrix->At(i * fIndex + j));
     delete [] name;
     return h2;
}




