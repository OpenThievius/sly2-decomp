// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "palette.h"
extern "C" int B_003DCFF8;
extern "C" PALETTE *B_003DCFFC;
extern "C" int B_003DCFF0;
extern "C" MATERIAL *B_003DCFF4;
extern "C" void FilterColorRgba8_1ed278(unsigned *);

extern "C" void func_001EA568(int dpv)
{
    for (int ipalette = 0; ipalette < B_003DCFF8; ipalette++) {
        PALETTE *ppalette = &B_003DCFFC[ipalette];
        if (ppalette->kind == 1) {
            ppalette->pdata = (unsigned *)(dpv + (sptr)ppalette->pdata);
            for (unsigned *pdwColor = ppalette->pdata; pdwColor < ppalette->pdata + ppalette->cword; pdwColor++)
                FilterColorRgba8_1ed278(pdwColor);
        }
    }
    if (B_003DCFF0 > 0) {
        int cmaterial = B_003DCFF0;
        MATERIAL *pmaterial = B_003DCFF4;
        do {
            cmaterial--;
            if (pmaterial->kind == 1)
                pmaterial->pdata = dpv + pmaterial->pdata;
            pmaterial++;
        } while (cmaterial != 0);
    }
}
