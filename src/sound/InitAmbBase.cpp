// SPDX-License-Identifier: GPL-3.0-or-later
#include "amb.h"
struct AMBVPTR { u8 unknown_0x0[0xC]; void *vptr; };
extern "C" {
extern u8 D_002D9D00[]; /* AMB's vtable: the class has no constructor of its own in source */

AMB *InitAmbBase(AMB *pamb)
{
    pamb->dle.next = 0;
    pamb->dle.prev = 0;
    ((AMBVPTR *)pamb)->vptr = D_002D9D00;
    pamb->volume = 1.0f;
    pamb->volAudible = 1.0f;
    pamb->lmMin = 300.0f;
    pamb->lmMax = 3000.0f;
    return pamb;
}
}
