// SPDX-License-Identifier: GPL-3.0-or-later
#include "amb.h"
struct AMBVPTR { u8 unknown_0x0[0xC]; void *vptr; };
extern "C" {
AMB *InitAmbBase(AMB *);
void SetAmbGrf(AMB *, s32, s32);
extern u8 D_002D9C70[]; /* the vtable of the emitter class InitAmb builds (overrides InitAmbBase's) */

AMB *InitAmb(AMB *pamb, s32 sfxid)
{
    InitAmbBase(pamb);
    pamb->sfxid = sfxid;
    ((AMBVPTR *)pamb)->vptr = D_002D9C70;
    SetAmbGrf(pamb, 1, 1);
    return pamb;
}
}
