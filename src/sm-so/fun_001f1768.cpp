#include "sly2.h"
#include "stepguard.h"
extern "C" void func_001F1768(STEPGUARD *pguard, int nArg) {
    if (pguard->fEnabled != 0) {
        GUARDACT *pguardact = &pguard->aguardact[pguard->cguardact++];
        pguardact->unkC = nArg;
        pguardact->oid = 0x2B3;
        pguardact->nArg = -1;
        pguardact->unk4 = 0;
    }
}
