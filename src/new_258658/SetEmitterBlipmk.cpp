// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
struct EMITB { u8 unknown_0x0[0xC0]; int block; };
struct EMITTER { u8 unknown_0x0[0xE4]; EMITB *pemitb; };
struct B16 { char b[16]; };
struct BLK { int kind; u8 unknown_0x4[0x2C]; B16 data; };
extern "C" BLK *PemitblipEnsureEmitter(EMITTER *, int);
extern float g_2bde00;
extern B16 D_002BDDF0;
extern "C" void SetEmitterBlipmk(EMITTER *emitter, int blipmk)
{
    BLK *blk = PemitblipEnsureEmitter(emitter, 1);
    if (blk->kind == blipmk || emitter->pemitb->block != 0)
        return;
    blk->kind = blipmk;
    if (blipmk != 1) {
        if (blipmk == 2)
            blk->data = D_002BDDF0;
    } else {
        *(float *)&blk->data = g_2bde00;
    }
}
