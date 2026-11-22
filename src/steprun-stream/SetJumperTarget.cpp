// SPDX-License-Identifier: GPL-3.0-or-later
#include "guard.h"
#include "step.h"
#include "xf.h"

#include "lookat.h"

extern "C" {
QW ConvertXfPos(int, XF *, QW);
void SetJumperTarget(JUMPER *pjumper, QW pos) {
    int state = pjumper->state;
    if (state == 0) {
        pjumper->posTarget = pos;
    } else if (state >= 0) {
        if (state < 3) {
            if (pjumper->fTrackTarget != 0) {
                LOOKATGOAL *plookat = pjumper->plookat;
                plookat->posTarget = ConvertXfPos(0, pjumper->pso->pxfLinear->pxfParent, pos);
            }
        }
    }
}
}
