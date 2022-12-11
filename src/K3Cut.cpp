#include "K3Cut.h"
ClassImp(K3Cut);

Int_t K3Cut::Count() 
{ 
    if (Is()) ++fCount; 
    return fCount;
}

Bool_t K3Cut::Check(Double_t value) 
{ 
    if (value < fMin || value > fMax) this->Off();
    else this->On();
    return fStat;
}
