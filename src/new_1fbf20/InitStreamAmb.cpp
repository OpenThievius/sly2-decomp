// SPDX-License-Identifier: GPL-3.0-or-later
#include "streamamb.h"
#include "sndsystem.h"
struct AMBVPTR { u8 unknown_0x0[0xC]; void *vptr; };
extern "C" AMB *InitAmbBase(AMB *);
extern "C" void SetAmbGrf(AMB *, int, int);
extern "C" void PauseAmb(AMB *);
extern "C" int func_001FD080(void *, int);
extern SNDSYSTEM B_003DD040;
extern char D_002D9BE0[]; /* the vtable of the stream emitter class */

extern "C" STREAMAMB *InitStreamAmb(STREAMAMB *amb, int record, int start)
{
    InitAmbBase(amb);
    amb->sfxid = record;
    ((AMBVPTR *)amb)->vptr = D_002D9BE0;
    amb->grfStart = start;
    for (int slot = 5; slot >= 0; --slot) {
        amb->vol[slot] = 1.0f;
    }
    SetAmbGrf(amb, 0x801, 0x801);
    SNDSYSTEM *psnd = &B_003DD040;
    int kind = func_001FD080(psnd, amb->sfxid);
    if (*(psnd->grid[2] + kind) == 0.0f) {
        PauseAmb(amb);
    }
    if (psnd->field_0x58) {
        PauseAmb(amb);
    }
    return amb;
}
