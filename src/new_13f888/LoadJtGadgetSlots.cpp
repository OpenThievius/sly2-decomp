#include "jt.h"
#include "cref.h"
extern "C" const char RO_002A4D50[];
extern "C" const char RO_002A4D58[];
extern "C" int sprintf(char *, const char *, ...);
extern "C" CRef func_001D8A38(const char *,  const char *, const char *, int);

void LoadJtGadgetSlots(JT *jt)
{
    GADGETSLOT *aslot = jt->aslot;
    for (int index = 0; index < 3; index++) {
        char name[16];
        sprintf(name, RO_002A4D50, index);
        aslot[index].gadget = func_001D8A38(jt->Slot103(), RO_002A4D58, name, 0).m_tag.m_n;
    }
    jt->Slot105();
}
