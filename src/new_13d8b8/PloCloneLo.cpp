// SPDX-License-Identifier: GPL-3.0-or-later
#include "lo.h"
#include "classinfo.h"
extern "C" LO *PloNew(int, int, int, int);
LO *PloCloneLo(LO *plo, int arg1) {
    LO *result;
    if (plo != 0) {
        CLASSINFO *pclassinfo = plo->Slot6();
        LO *clone = PloNew(pclassinfo->cid, arg1, plo->oid, -1);
        clone->CloneVirtual(plo);
        result = clone;
    } else {
        result = 0;
    }
    return result;
}
