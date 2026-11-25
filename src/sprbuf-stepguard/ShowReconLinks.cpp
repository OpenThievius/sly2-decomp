// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "recon.h"
extern "C" void ShowReconLinks(BINOCRECON *precon)
{
    for (int itarget = 0; itarget < precon->ctarget; ++itarget) {
        RECON *ptarget = precon->aptarget[itarget];
        if (((ptarget->grfo >> 60) & 1) == 0)
            continue;
        LO *plink = ptarget->plink;
        if (plink != 0)
            plink->Add();
    }
}
