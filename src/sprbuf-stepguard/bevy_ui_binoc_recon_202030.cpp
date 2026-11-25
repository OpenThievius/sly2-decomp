// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "recon.h"
extern "C" void bevy_ui_binoc_recon_202030(BINOCRECON *precon)
{
    precon->clist = 0;
    for (int itarget = 0; itarget < precon->ctarget; ++itarget) {
        RECON *ptarget = precon->aptarget[itarget];
        if (ptarget->idList == -1)
            continue;
        TASK *ptask = ptarget->ptask;
        if (ptask != 0) {
            int state = ptask->state;
            if (state != 1) {
                if (state != 2)
                    continue;
            }
        }
        unsigned count = precon->clist;
        if (count < 5) {
            precon->aptargetList[count] = ptarget;
            precon->clist = count + 1;
        }
    }
}
