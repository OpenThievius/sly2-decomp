/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "bentleyview.h"

s32 FIsPoSwFocusBase(void *ppo);
u32 GrfbtnJtGadget(void *pbentley, s32 gadget);
void func_00141E70(void);
void func_001F6978(void *pso, s32 oid);
void func_001F69F8(void *pso, s32 oid);

void UpdateBentleyGadgetGlob(struct BENTLEYVIEW *pbentley) {
    func_00141E70();
    if ((FIsPoSwFocusBase(pbentley) != 0) && (GrfbtnJtGadget(pbentley, 0xC) != 0)) {
        func_001F6978(pbentley, 0x24D);
        return;
    }
    func_001F69F8(pbentley, 0x24D);
}
