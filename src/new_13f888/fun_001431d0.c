/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"
#include "jtview.h"

struct GOALGRAB *GoalStack_PgoalFind(struct GOALSTACK *pgoalstack, s32 classId);

void func_001431D0(struct JTVIEW *pjt) {
    struct STEPGUARDVIEW *pguard = (struct STEPGUARDVIEW *)pjt->field_0x10DC;
    struct GOALGRAB *pgoalGrab;
    if (pguard != 0) {
        pgoalGrab = GoalStack_PgoalFind(&pguard->goalstack, 0xB1);
        if ((pgoalGrab != 0) && (pgoalGrab->psoHeld == (struct SO *)pjt)) {
            pgoalGrab->field_0x60 = 0;
        }
    }
}
