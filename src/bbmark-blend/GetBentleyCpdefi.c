/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "bentleyview.h"
#include "clock.h"

void GetJtCpdefi(void *pbentley, s32 *pgrf);
void func_0019EA00(void *ppipe, s32 *pgrf);

void GetBentleyCpdefi(struct BENTLEYVIEW *pbentley, s32 *pgrf) {
    s32 stateBefore;
    s32 stateAfter;

    stateBefore = pbentley->state;
    if (stateBefore != 0) {
        if ((stateBefore != 9) && (pbentley->field_0x4CC != 0)) {
            pbentley->field_0x1080 = (f32) g_2dded0.t;
        }
    }
    GetJtCpdefi(pbentley, pgrf);
    stateAfter = pbentley->state;
    switch (stateAfter) {
    case 13:
        func_0019EA00(pbentley->pipe, pgrf);
        return;
    case 5:
        *pgrf |= 1;
        return;
    }
}
