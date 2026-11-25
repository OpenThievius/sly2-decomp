#include "asega.h"
/* The event table of an ASEG as these functions read it: a count at 0xA0 and the events at 0xA4 (asega.h names the two words iea and paea) */
struct ASEGEVENTTABLE { u8 unknown_0x0[0xA0]; s32 cea; ASEGEVENT *aea; };
static inline ASEGEVENTTABLE *PtableOf(ASEGA *pasega) { return (ASEGEVENTTABLE *)pasega->paseg; }

extern "C" void UpdateAsegaIeaCur__FP5ASEGA(ASEGA *pasega)
{
    int cea = PtableOf(pasega)->cea;
    if (cea == 0)
        return;
    int iea = cea;
    if (pasega->svtLocal >= 0.0f) {
        for (iea = 0; iea < PtableOf(pasega)->cea; iea++) {
            if (pasega->tLocal <= PtableOf(pasega)->aea[iea].tLocal)
                break;
        }
        pasega->iea = iea;
        return;
    }
    for (iea--;; iea--) {
        if (iea < 0 || PtableOf(pasega)->aea[iea].tLocal <= pasega->tLocal)
            goto found;
    }
found:
    pasega->iea = iea + 1;
}
