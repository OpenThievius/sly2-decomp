// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
#include "clock.h"
#include "sw.h"
#include "ps2inline.h"
#include "vu0inline.h"
extern "C" {
void func_00174950(GOAL *pgoal);
MATRIX3 *PmatLoWorld(void *plo);
QW PosLoWorld(void *plo);
float atan2f(float, float);
void func_00209818(void *, float);
float RadNormalize__Ff(float);
QW SetVectorCylind__FP6VECTORfff(float, float, float);
void SetJumperTarget(void *ptarget, QW position);
void func_0020AB68(STEPGUARD *pguard, void *panim, int mode, QW vec);
void func_001EEFC0(GOAL *pgoal);
void ReplaceSwHitFx(SW *pworld, int, QW, STEPGUARD *pguard, void *pfx);
int PpoSwFocusBase(SW *pworld);
int func_001A6AF8(int, int);
void TriggerJoyRumbleRumk__FP3JOY4RUMKf(void *pjoy, int, float);
extern SW B_003DD490;
extern char B_002DFC00[];
extern QW g_2a2dd0;
extern int g_2f7900;
void GoalHit_Activate(GOALHIT *pgoal) {
    func_00174950(pgoal);
    QW squares = SquaredLength(pgoal->args.vecVelocity.q);
    int moving = 0;
    float length = LaneX(SqrtX(squares));
    if (0.0001f < length)
        moving = pgoal->args.grfHit != 0x40000;
    float heading;
    if (moving) {
        heading = atan2f(-pgoal->args.vecVelocity.f[1], -pgoal->args.vecVelocity.f[0]);
    } else {
        MATRIX3 *pmat = PmatLoWorld(pgoal->pstep);
        heading = atan2f(pmat->mat[0][1], PmatLoWorld(pgoal->pstep)->mat[0][0]);
    }
    func_00209818(&((STEPGUARD *)pgoal->pstep)->heading, heading);
    if (pgoal->panimref) {
        if (pgoal->panimref->kind == 2) {
            QW cylinder = SetVectorCylind__FP6VECTORfff(
                RadNormalize__Ff(pgoal->pstep->radHeading + 3.1415927f),
                ((JUMPANIM *)pgoal->panimref->pdata)->distance, 0.0f);
            QW position = PosLoWorld(pgoal->pstep);
            ANIMREF *panimref = pgoal->panimref;
            QW target = VectorAdd(position, cylinder);
            SetJumperTarget(panimref->pinst, target);
        }
    }
    func_0020AB68((STEPGUARD *)pgoal->pstep, 0, 0, g_2a2dd0);
    if (pgoal->state == 0)
        func_001EEFC0(pgoal);
    ReplaceSwHitFx(&B_003DD490, 1, PosLoWorld(pgoal->pstep), (STEPGUARD *)pgoal->pstep, &((STEPGUARD *)pgoal->pstep)->field_0x35C);
    pgoal->tLimit = 3.4028235e38f;
    pgoal->tJolt = 3.4028235e38f;
    ((STEPGUARD *)pgoal->pstep)->field_0xF04 = 0;
    if (((STEPGUARD *)pgoal->pstep)->field_0x334 != 0) {
        int focus = PpoSwFocusBase(&B_003DD490);
        if (focus != 0) {
            if (func_001A6AF8(pgoal->args.arg, focus) != 0) {
                if (focus == g_2f7900 || (pgoal->args.grfHit & 0x40000) != 0) {
                    TriggerJoyRumbleRumk__FP3JOY4RUMKf(B_002DFC00, 3, 0.15f);
                    pgoal->tJolt = g_2dded0.t + 0.050000004f;
                }
            }
        }
        pgoal->tLimit = g_2dded0.t + 0.13333334f;
    }
}
}
