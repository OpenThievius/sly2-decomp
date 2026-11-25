// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "emitter.h"
struct B16 { char b[16]; };
extern "C" EMITPARAMS *func_00259330(EMITTER *, int);
extern float g_2bde00;
extern B16 D_002BDDF0;
extern "C" void func_00259830(EMITTER *emitter, int blipmk)
{
    EMITPARAMS *blk = func_00259330(emitter, 1);
    if (blk->kind == blipmk || emitter->pemitb->params.kind != 0)
        return;
    blk->kind = blipmk;
    if (blipmk != 1) {
        if (blipmk == 2)
            *(B16 *)&blk->payload = D_002BDDF0;
    } else {
        *(float *)&blk->payload = g_2bde00;
    }
}
