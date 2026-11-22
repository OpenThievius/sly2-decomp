// SPDX-License-Identifier: GPL-3.0-or-later
#include "guard.h"
#include "step.h"
#include "xf.h"
struct SW;
extern SW B_003DD490;
extern "C" {
void RecalcSwOxfFilterForObject(SW *, SO *);
void SetXfKind(SO *, XF *, int);
void func_0012E460(LOOKATGOAL **pplookat);

void EndJumperFlight(JUMPER *pjumper) {
    STEP *psoXf;
    STEP *psoFilter;
    if (pjumper->fTrackTarget != 0) {
        pjumper->fTrackTarget = 0;
        if (pjumper->plookat != 0) {
            func_0012E460(&pjumper->plookat);
            psoXf = pjumper->pso;
            SetXfKind(psoXf, psoXf->pxfLinear, 2);
            psoFilter = pjumper->pso;
            psoFilter->grfso &= ~(u64)0x4000000;
            RecalcSwOxfFilterForObject(&B_003DD490, pjumper->pso);
        }
    }
}
}
