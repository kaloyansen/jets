#ifndef __K3Subtrigger__
#define __K3Subtrigger__
#include "K3Cut.h"

class K3Subtrigger : public K3Cut {
public:
    Int_t num;
    Float_t pf;

    K3Subtrigger();

    ClassDef(K3Subtrigger,1); // Class to control subtriggers
};

#endif
