// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "recon.h"
extern "C" void ClearReconVisibility(BINOCRECON *precon)
{
    for (int itarget = 0; itarget < precon->ctarget; ++itarget)
        precon->aptarget[itarget]->vis = 0;
}
