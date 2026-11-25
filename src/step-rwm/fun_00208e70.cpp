/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
#include "jt.h"
extern "C" {
extern const float D_FLT_002C3D90;
extern const float D_FLT_002C3D94;
void GetJtFocusScore(JT *, STEPGUARD *, s32 *, float *, float *);
u64 GrfsgsFromSgs(int);
int FIsGuardInSgs(STEPGUARD *, int);
GOAL *func_00205458(STEPGUARD *, int);
int FIsBasicDerivedFrom(void *, int);
int func_00227C90(LO *, QW);
QW PosLoWorld(LO *);
}
struct LM;
int FCheckLm(LM *, float);
int func_00208E70(STEPGUARD *pguard, JT *pjt, float *pscore)
{
    float sg[2];
    GetJtFocusScore(pjt, pguard, &pjt->field_0x10DC, &sg[0], &sg[1]);
    if (pscore != 0)
        *pscore = sg[0];
    if ((pguard->grfsgs & GrfsgsFromSgs(1)) == 0) {
        if (pguard->field_0x364 != 0 && pjt->field_0x10F0 != 0) {
            BASIC *pheld;
            if (FIsGuardInSgs(pguard, 0x1D)) {
                pheld = pguard->pbasicAlert;
            } else if (FIsGuardInSgs(pguard, 5)) {
                pheld = (BASIC *)((GOALHIT *)func_00205458(pguard, 0xA1))->args.arg;
            } else if (FIsGuardInSgs(pguard, 6)) {
                pheld = (BASIC *)((GOALHIT *)func_00205458(pguard, 0xA2))->args.arg;
            } else if (FIsGuardInSgs(pguard, 0x17)) {
                pheld = ((GOALGRAB *)func_00205458(pguard, 0xB1))->psoHeld;
                if (pheld == pjt)
                    *pscore = *pscore + D_FLT_002C3D90;
            } else {
                pheld = 0;
            }
            if (pheld != 0) {
                if (pheld == pjt)
                    return 4;
                if (FIsBasicDerivedFrom(pheld, 0x34))
                    return 4;
            }
        }
        LO *pvolume;
        if ((sptr)pguard == pjt->field_0x10DC && pjt->focusKind == 3)
            pvolume = pguard->field_0x3F8;
        else
            pvolume = pguard->field_0x3F4;
        if (pvolume != 0 && ((int)(pvolume->grfo >> 60) & 1) != 0) {
            if (func_00227C90(pvolume, PosLoWorld(pjt)))
                return 3;
        }
    }
    LM *plm = (LM *)(FIsGuardInSgs(pguard, 0x17) ? pguard->field_0x368 : pguard->field_0x370);
    if (sg[0] <= pguard->field_0x378 * D_FLT_002C3D94 && FCheckLm(plm, sg[1]) && pguard->field_0x364 != 0)
        return 2;
    if (sg[0] <= pguard->field_0x388) {
        if (!FCheckLm((LM *)pguard->field_0x380, sg[1]))
            return 0;
        if (pguard->field_0x37C != 0)
            return 1;
    }
    return 0;
}
