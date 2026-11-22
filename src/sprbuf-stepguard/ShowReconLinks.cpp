// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "so.h"
/* One reader on a guessed class: ShowReconLinks reads SO word 0x100 as an LO (slot 8 called). Not in so.h. */
struct SORECON {
    u8 unknown_0x0[0x100];
    /* 0x100 */ LO *plo;
};
struct RECON { char pad[0x30]; int ctarget; SO *aptarget[1]; };
extern "C" void ShowReconLinks(RECON *precon)
{
    for (int itarget = 0; itarget < precon->ctarget; ++itarget) {
        SO *ptarget = precon->aptarget[itarget];
        if (((ptarget->grfo >> 60) & 1) == 0)
            continue;
        LO *plink = ((SORECON *)ptarget)->plo;
        if (plink != 0)
            plink->Add();
    }
}
