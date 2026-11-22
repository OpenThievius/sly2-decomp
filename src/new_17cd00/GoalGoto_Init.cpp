// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
struct GLOBAL3E1A5C {
    u8 unknown_0x0[0x28];
    s32 field_0x28;
};
extern "C" {
void func_001EEF68(GOALGOTO *pgoal);
extern GLOBAL3E1A5C *B_003E1A5C;

// Member stores (pgoal->state = -1 and the others) let gcc hoist the load of B_003E1A5C above them (score 10); retail's
// order needs the stores through a byte pointer, so the offsets stay casts here.
void GoalGoto_Init(GOALGOTO *pgoal) {
    char *base = (char *)pgoal;
    func_001EEF68(pgoal);
    *(f32 *)(base + 0xA0) = -3.4028235e38f;
    *(s32 *)(base + 0x30) = -1;
    *(s32 *)(base + 0x38) = -1;
    *(s32 *)(base + 0xA4) = B_003E1A5C->field_0x28;
}

}
