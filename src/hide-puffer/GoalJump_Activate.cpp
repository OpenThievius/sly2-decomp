// SPDX-License-Identifier: GPL-3.0-or-later
#include "vu0inline.h"
#include "ps2inline.h"
#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
#include "goal.h"

struct JT;
struct PIPE;
/* The jump target when it derives from class 0x13: GoalJump_Activate reads its word 0x124 (3 selects the surface goal). One reader on a guessed class: a local view. */
struct LOCLASS13VIEW {
    u8 unknown_0x0[0x124];
    /* 0x124 */ s32 state;
};
/* the difference of a vector read through a reference (retail keeps the minuend in memory) */
static inline QW VectorSubFrom(const QW &first, QW second)
{
    return VectorSub(first, second);
}

extern "C" {
u64 GrfsgsFromSgs(int sgs);
int FIsBasicDerivedFrom(void *pbasic, int cid);
QW PosLoWorld(LO *plo);
MATRIX4 *PmatLoWorld(LO *plo);
void FindCrvClosestPointAll(void *pcrv, QW pos, int, QW *ppos, VECTOR *pdir, int, float *pu);
float atan2f(float y, float x);
float RadNormalize__Ff(float rad);
MATRIX3Q LoadRotateMatrixRad(QW axis, float rad);
MATRIX3Q BuildOrthonormalMatrixY__FP6VECTORT0P7MATRIX3(QW vecY, QW vecZ);
void GetJtPipeGoalMat__FP2JTP4PIPEfP7MATRIX3(JT *pjt, PIPE *ppipe, float u, MATRIX3Q *pmat);
int FFindSurfaceAlongUp(QW *ppos, int, int, float, float);
void func_0017A468(GOALJUMP *pgoal);
void func_00174950(GOALJUMP *pgoal);
void func_001EEFC0(GOALJUMP *pgoal);
void func_00209818(void *p, float rad);
void func_00209840(void *p, MATRIX3Q *pmat);
void SetJumperTarget(JUMPER *pjumper, QW pos);
extern QW g_2a2dc0;
extern float g_2be6b8[2];
extern u64 g_2dfb70;
extern int g_2dfb78;

void GoalJump_Activate(GOALJUMP *pgoal)
{
    if (g_2dfb78 == 0) {
        u64 grfsgs0 = GrfsgsFromSgs(0x1B);
        u64 grfsgs1 = GrfsgsFromSgs(0x27);
        u64 grfsgs2 = GrfsgsFromSgs(0x28);
        u64 grfsgs3 = GrfsgsFromSgs(0x29);
        g_2dfb78 = 1;
        g_2dfb70 = grfsgs0 | grfsgs1 | grfsgs2 | grfsgs3;
    }
    STEPGUARD *pstepguard = (STEPGUARD *)pgoal->pstep;
    u64 grfsgsSaved = pstepguard->grfsgs & g_2dfb70;
    pstepguard->grfsgs = pstepguard->grfsgs & ~g_2dfb70;
    u64 grfsgsAdd = 0;
    if (pgoal->ploTarget != 0) {
        float u;
        float rad;
        if (FIsBasicDerivedFrom(pgoal->ploTarget, 0xA) != 0) {
            VECTOR dir;
            LO *pcrv = pgoal->ploTarget;
            FindCrvClosestPointAll(pcrv, PosLoWorld(pgoal->pstep), 0, &pgoal->posTarget, &dir, 0, &u);
            rad = atan2f(dir.y, dir.x);
        } else {
            pgoal->posTarget = PosLoWorld(pgoal->ploTarget);
            MATRIX4 *pmat = PmatLoWorld(pgoal->ploTarget);
            rad = atan2f(pmat->mat[0][1], PmatLoWorld(pgoal->ploTarget)->mat[0][0]);
        }
        if (FIsBasicDerivedFrom(pgoal->ploTarget, 0xD) != 0) {
            grfsgsAdd |= GrfsgsFromSgs(0x1B);
            if (pgoal->fFacing == 0)
                rad = RadNormalize__Ff(rad + 3.1415927f);
            pgoal->fMatrix = 1;
            pgoal->mat = LoadRotateMatrixRad(g_2a2dc0, rad);
        } else if (FIsBasicDerivedFrom(pgoal->ploTarget, 0x27) != 0) {
            grfsgsAdd |= GrfsgsFromSgs(0x29);
        } else if (FIsBasicDerivedFrom(pgoal->ploTarget, 0xB) != 0) {
            grfsgsAdd |= GrfsgsFromSgs(0x27);
            pgoal->fMatrix = 1;
            GetJtPipeGoalMat__FP2JTP4PIPEfP7MATRIX3((JT *)pgoal->ploTarget, pgoal->ppipe, u, &pgoal->mat);
            func_0017A468(pgoal);
        } else if (FIsBasicDerivedFrom(pgoal->ploTarget, 0x13) != 0 && ((LOCLASS13VIEW *)pgoal->ploTarget)->state == 3) {
            grfsgsAdd |= GrfsgsFromSgs(0x28);
            pgoal->fMatrix = 1;
            pgoal->mat = BuildOrthonormalMatrixY__FP6VECTORT0P7MATRIX3(PmatLoWorld(pgoal->ploTarget)->row[0], g_2a2dc0);
            func_0017A468(pgoal);
        } else {
            FFindSurfaceAlongUp(&pgoal->posTarget, 1, 0, g_2be6b8[1], g_2be6b8[0]);
            pgoal->ploTarget = 0;
        }
    }
    ((STEPGUARD *)pgoal->pstep)->grfsgs |= grfsgsAdd;
    func_00174950(pgoal);
    ((STEPGUARD *)pgoal->pstep)->grfsgs &= ~grfsgsAdd;
    ((STEPGUARD *)pgoal->pstep)->grfsgs |= grfsgsSaved;
    if (pgoal->panimref != 0) {
        switch (((STEPGUARD *)pgoal->pstep)->modePath) {
        case -1:
        case 0:
        case 3: {
            QW pos = pgoal->posTarget;
            QW dir = VectorSubFrom(pos, PosLoWorld(pgoal->pstep));
            func_00209818(&((STEPGUARD *)pgoal->pstep)->heading, atan2f(LaneYInGeneralRegister(dir), LaneX(dir)));
            break;
        }
        case 2: {
            QW pos = pgoal->posTarget;
            QW dir = VectorSubFrom(pos, PosLoWorld(pgoal->pstep));
            MATRIX3Q mat = BuildOrthonormalMatrixY__FP6VECTORT0P7MATRIX3(PmatLoWorld((LO *)((STEPGUARD *)pgoal->pstep)->ptargetPath)->row[0], dir);
            func_00209840(&((STEPGUARD *)pgoal->pstep)->heading, &mat);
            break;
        }
        }
        ((JUMPER *)pgoal->panimref->pinst)->fTrackTarget = pgoal->fTrackTarget;
        ((JUMPER *)pgoal->panimref->pinst)->ploTarget = pgoal->ploTarget;
        ((JUMPER *)pgoal->panimref->pinst)->fFacing = pgoal->fFacing;
        SetJumperTarget((JUMPER *)pgoal->panimref->pinst, pgoal->posTarget);
    }
    func_001EEFC0(pgoal);
}
}
