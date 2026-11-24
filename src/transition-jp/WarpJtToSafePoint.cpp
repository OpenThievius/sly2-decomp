// SPDX-License-Identifier: GPL-3.0-or-later
#include "jt.h"
#include "xf.h"
#include "phys.h"
#include "sw.h"
#include "ps2inline.h"
#include "vu0inline.h"

struct SAFEPT { void *pbasic; s32 field4; u8 unknown_0x8[8]; QW second; };

struct CMG { u8 unknown_0x0[0x60]; QW dir; };
extern CMG B_002DDF40;
extern SW B_003DD490;
extern f32 D_FLT_002BF940;

extern "C" {
void FindBestSafePoint(void *, void *);
void *PpoSwFocusBase(void *);
QW func_0019F3F8(void *, void *, float);
float DtSolveJumpLaunch(QW, QW, float, float, float, float);
void SetStepRadTargetDir(void *, QW);
int SetResetFlag__FP2CM(void *);
void SetJmpState(void *, int, int, int);
int FIsBasicDerivedFrom(void *, int);
void JtbsChooseJtLanding(void *, void *);
void func_00148300(void *, void *);
void StartFade(int);
}

void WarpJtToSafePoint(JT *pjt, SAFEPT *ppoint)
{
    SAFEPT point;
    QW launch;
    if (ppoint == 0) {
        FindBestSafePoint(pjt->PvPart9E0(), &point);
        ppoint = &point;
        if (pjt == PpoSwFocusBase(&B_003DD490)) {
            launch = func_0019F3F8(pjt, &point, 0.0f);
            QW toward = VectorSub(launch, pjt->pxfLinear->matWorld.row[3]);
            float reach = DtSolveJumpLaunch(toward, pjt->pphys->dvGravity, 1000.0f, -1000.0f, 1.0f, -1.0f);
            if (D_FLT_002BF940 < reach) {
                QW offset = VectorSub(launch, pjt->posLocal);
                s32 saved = pjt->field_0x9E4;
                pjt->TranslateToPos(offset);
                pjt->field_0x9E4 = saved;
                SetStepRadTargetDir(pjt, B_002DDF40.dir);
                pjt->Slot30(&pjt->matHeading);
                SetResetFlag__FP2CM(&B_002DDF40);
                SetJmpState(pjt->PvJmp(), 0xB, 0, 0);
                if (point.field4 != 0 &&
                    (FIsBasicDerivedFrom(point.pbasic, 0x13) || FIsBasicDerivedFrom(point.pbasic, 0xB) ||
                     FIsBasicDerivedFrom(point.pbasic, 0xD) || FIsBasicDerivedFrom(point.pbasic, 0x27) ||
                     FIsBasicDerivedFrom(point.pbasic, 0xC) || FIsBasicDerivedFrom(point.pbasic, 0x22) ||
                     FIsBasicDerivedFrom(point.pbasic, 0x26))) {
                    func_00148300(&B_003DD490, point.pbasic);
                    JtbsChooseJtLanding(pjt->PvJmp(), point.pbasic);
                }
                StartFade(B_003DD490.field_0x3E60);
                return;
            }
        }
    }
    pjt->field_0x490 = *(QW *)ppoint;
    pjt->field_0x4A0 = ppoint->second;
    SetJmpState(pjt->PvJmp(), 0xA, 0, 0);
}
