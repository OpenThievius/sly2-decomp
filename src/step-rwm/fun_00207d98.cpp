// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
extern "C" {
s32 GrfsgsFromRef(s32);
GUARDANIM *PguardanimEnsure(STEPGUARD *, s64);
void func_0020BD78(s32 *);
JUMPANIM *func_0020C010(s32);

void func_00207D98(STEPGUARD *pguard, s32 refList, s32 idJump) {
    JUMPANIM *pjump;
    GUARDANIM *panim;

    panim = PguardanimEnsure(pguard, GrfsgsFromRef(refList));
    panim->ref.kind = 2;
    pjump = func_0020C010(0x40);
    panim->ref.pdata = pjump;
    func_0020BD78(&pjump->field_0x0);
    ((JUMPANIM *)panim->ref.pdata)->field_0x0 = idJump; /* reloaded through the slot, as retail does */
    panim->ref.grf = 0;
}

}
