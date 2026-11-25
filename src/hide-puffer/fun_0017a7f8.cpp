// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "goal.h"
#include "step.h"
struct GOAL_17A7F8 : GOAL {
    int state;
    u8 unknown_0x34[0x4];
    float tEffect;
};
#include "sw.h"
extern "C" void func_001EEF98(void);
extern "C" void func_0017A8C8(GOAL_17A7F8 *, int);
extern "C" QW PosLoWorld(STEP *);
extern "C" int *PhitfxSpawn(BASIC *, QW, STEP *);
extern "C" SW B_003DD490;
extern "C" float D_FLT_002BE6C0, g_2dded0;
void func_0017A7F8(GOAL_17A7F8 *pgoal)
{
    func_001EEF98();
    int state;
    for (;;) {
        state = pgoal->state;
        if (state < 4) {
            if (state >= 2) {
                if (pgoal->pstep->psoSurface != 0)
                    func_0017A8C8(pgoal, -1);
            }
        }
        if (state == pgoal->state)
            break;
    }
    if (state == 1 || state == 4) {
        if (D_FLT_002BE6C0 < g_2dded0 - pgoal->tEffect) {
            pgoal->tEffect = g_2dded0;
            int *pfx = PhitfxSpawn(B_003DD490.phitfxdef, PosLoWorld(pgoal->pstep), pgoal->pstep);
            pfx[0x54 / 4] = 3;
        }
    }
}
