#ifndef __K3Trigger__
#define __K3Trigger__
#include "TObject.h"

class K3Trigger: public TObject {
public:
    Byte_t l1te,l2te,l1rw,l1ac,l1l2rw,l1l3rw,l1l2l3ac,l4vst,Trigac,l4class;    
    K3Trigger() { l1te=l2te=l1rw=l1ac=l1l2rw=l1l3rw=l1l2l3ac=l4vst=Trigac=l4class=0; }
    K3Trigger(Byte_t,Byte_t,Byte_t,Byte_t,Byte_t,Byte_t,Byte_t,Byte_t,Byte_t,Byte_t);
    ClassDef(K3Trigger,4); // Base class for trigger info
};

#endif

