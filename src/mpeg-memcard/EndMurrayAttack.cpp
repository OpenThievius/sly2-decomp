// SPDX-License-Identifier: GPL-3.0-or-later
#include "murray.h"
struct PAIR { s32 idFilter; s32 dofFilter; };
extern "C" {
void SetMurrayState(MURRAY *, s32);
void func_00131B60(ASEGA *, LO *, s32, PAIR *);
extern PAIR D_002C09F8[5];

void EndMurrayAttack(MURRAY *pmurray) {
    ASEGA *pasega;

    func_00131B60((ASEGA *)pmurray->field_0x1030, pmurray, 5, D_002C09F8);
    pasega = (ASEGA *)pmurray->field_0x1030;
    pmurray->field_0x1030 = 0;
    pmurray->field_0x190C = pasega;
    SetMurrayState(pmurray, 0);
}

}
