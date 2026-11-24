// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "ps2inline.h"
#include "vu0inline.h"
#include "sly.h"
#include "stepguard.h"
#include "goals.h"
#include "joy.h"
extern "C" {
QW PosLoWorld(void *);
int FCheckLm__FP2LMf(LM *, float);
void *GoalStack_PgoalFind(GOALSTACK *, int);
void SetJtState(SLY *, int, int);
int FCheckJtCaneSide(SLY *);
float atan2f(float, float);
float RadNormalize__Ff(float);
extern float D_002BF4AC;
extern LM D_002BF4B0;
}
extern "C" int ChooseJtCaneSwing(SLY *pjt)
{
    STEPGUARD *pbody = (STEPGUARD *)pjt->field_0x10DC;
    if (pbody != 0) {
        QW position = PosLoWorld(pbody);
        QW difference = VectorSub(position, PosLoWorld(pjt));
        int near = 0;
        if (LaneX(SqrtX(SquaredLengthXy(difference))) < D_002BF4AC)
            near = FCheckLm__FP2LMf(&D_002BF4B0, LaneZInGeneralRegister(difference)) != 0;
        if (near) {
            GOALGRAB *pgoal = (GOALGRAB *)GoalStack_PgoalFind(((STEPGUARD *)pjt->field_0x10DC)->pgoalstack(), 0xB1);
            if (pgoal != 0 && pgoal->psoHeld == pjt) {
                int state = pgoal->phase;
                if (state < 2) {
                    if (state >= 0) {
                        SetJtState(pjt, 0x10, -1);
                        return -1;
                    }
                }
            }
        }
    }
    int swing;
    if (pjt->field_0x18D0 == 5) {
        MATRIX4 *pforward = pjt->PmatWorld();
        float forwardX = pjt->PmatWorld()->mat[0][0];
        float diff = RadNormalize__Ff(pjt->pjoy->radStick - atan2f(pforward->mat[0][1], forwardX));
        float magnitude = diff < 0.0f ? -diff : diff;
        if (magnitude < 0.7853982f)
            swing = 0xE;
        else if (2.3561945f < magnitude)
            swing = 0x10;
        else if (0.0f < diff)
            swing = 0x12;
        else
            swing = 0x14;
    } else {
        swing = pjt->jts == 0 ? 0xC : 0xE;
    }
    switch (pjt->jtcs) {
    case 12: case 14: case 16: case 18: case 20:
        swing += 1;
        break;
    case 13: case 15: case 17: case 19: case 21:
        break;
    default:
        if (FCheckJtCaneSide(pjt) != 0)
            swing += 1;
        break;
    }
    return swing;
}
