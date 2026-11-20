#include "sly2.h"
struct EA { float tLocal; int pad[3]; };
struct ASEG { char pad[0xA0]; int cea; EA *aea; };
struct ASEGA { char pad[0x14]; ASEG *paseg; char pad18[4]; float tLocal; char pad20[0x20]; float svtLocal; char pad44[0xC]; int ieaCur; };

extern "C" void UpdateAsegaIeaCur__FP5ASEGA(ASEGA *pasega)
{
    int cea = pasega->paseg->cea;
    if (cea == 0)
        return;
    int iea = cea;
    if (pasega->svtLocal >= 0.0f) {
        for (iea = 0; iea < pasega->paseg->cea; iea++) {
            if (pasega->tLocal <= pasega->paseg->aea[iea].tLocal)
                break;
        }
        pasega->ieaCur = iea;
        return;
    }
    for (iea--;; iea--) {
        if (iea < 0 || pasega->paseg->aea[iea].tLocal <= pasega->tLocal)
            goto found;
    }
found:
    pasega->ieaCur = iea + 1;
}
