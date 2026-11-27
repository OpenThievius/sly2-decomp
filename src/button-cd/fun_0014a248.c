/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goalpatrol.h"
#include "guardview.h"

struct SNDMANAGER;

void Goal_Deactivate(struct GOALPATROL *pgoal);
void RemoveGuardSgs(struct STEPGUARD *pguard, s32 sgs);
void func_0014AE38(struct GOALPATROL *pgoal, s32 state);
void func_001FEEA0(struct SNDMANAGER *psndmanager);
extern struct SNDMANAGER B_003DD040;

void func_0014A248(struct GOALPATROL *pgoal) {
    Goal_Deactivate(pgoal);
    func_0014AE38(pgoal, -1);
    RemoveGuardSgs(pgoal->pstep, 0x24);
    func_001FEEA0(&B_003DD040);
    ((struct STEPGUARDVIEW *)pgoal->pstep)->field_0x4A4 = 1;
}
