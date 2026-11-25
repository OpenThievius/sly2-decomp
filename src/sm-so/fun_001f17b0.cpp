#include "sly2.h"
#include "stepguard.h"
extern "C" void func_001F17B0(STEPGUARD *pguard, int oid) {
    if (pguard->cguardact <= 0 || pguard->fEnabled != 0) {
        GUARDACT *pguardact = &pguard->aguardact[pguard->cguardact++];
        pguardact->oid = oid; pguardact->nArg = -1; pguardact->unk4 = 0; pguardact->unkC = 1;
    }
}
