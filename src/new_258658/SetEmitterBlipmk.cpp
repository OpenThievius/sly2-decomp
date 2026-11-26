// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "emitter.h"
struct B16 { char b[16]; };
extern "C" EMITPARAMS *PemitblipEnsureEmitter(EMITTER *, int);
extern float g_2bde00;
extern B16 D_002BDDF0;
extern "C" void SetEmitterBlipmk(EMITTER *emitter, int blipmk)
{
    EMITPARAMS *blk = PemitblipEnsureEmitter(emitter, 1);
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
