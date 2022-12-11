#ifndef __K3Space__
#define __K3Space__
#include "TClonesArray.h"
#include "TH2D.h"
#include "K3Cut.h"
#include <math.h>

class K3Space : public TObject {

     TClonesArray * fArray;
     TArrayD      * fCorrelationMatrix;
     

public:
     K3Space();
     ~K3Space();

     Int_t          fIndex;

     void           FillCorrelationMatrix(Double_t weight = 1);
     void           Set(TString name, Bool_t what = kTRUE);
     void           Off(TString name = "switch_off_all");
     void           On(TString name = "switch_on_all");
     void           Print();
     void           State();
     Bool_t         Is(TString name);
     Bool_t         Check(TString name, Double_t value);
     Int_t          Count(TString name);
     Int_t          Encode();

     TString      * Names();
     TString        Decode(Int_t code);
     TH2D         * CorrelationMatrixHistogram();
     K3Cut        * Add(TString name, Double_t min = -1e9, Double_t max = 1e9);
     K3Cut        * Get(TString name);

     ClassDef(K3Space,1); // Array of phase space cuts
};



#endif
