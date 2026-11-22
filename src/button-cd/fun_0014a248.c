/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goalpatrol.h"

/* STEPGUARD's word 0x4A4 (stepguard.h field_0x4A4; the C view guardview.h does not list it) */
struct STEPGUARDFLAGVIEW {
    u8 unknown_0x0[0x4A4];
    s32 field_0x4A4;
};
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
    ((struct STEPGUARDFLAGVIEW *)pgoal->pstep)->field_0x4A4 = 1;
}
