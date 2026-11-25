// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
#include "po.h"
#include "emitter.h"
extern "C" void func_001A58D0(EMITTER *, LO *, int);
extern "C" void func_001C48C0(SW *psw)
{
    for (int iemitter = 0; iemitter < psw->cemitter; iemitter++) {
        EMITTER *pemitter = psw->aemitter[iemitter];
        pemitter->pemitb->pinfo->plo = psw->ppoFocusBase;
        func_001A58D0(pemitter, psw->ppoFocusBase, 0);
    }
}
