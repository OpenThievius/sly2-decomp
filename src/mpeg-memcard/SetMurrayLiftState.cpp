// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "lo.h"
#include "so.h"
#include "xf.h"
#include "murray.h"
#include "carry.h"
#include "asega.h"
/* An IK limb record (0xE0 bytes, MURRAY::pikLimbA/B): LoadMurrayFromBrx stores three transform handles at +4, +8 and +0xC and binoc_joy_186610's
   record has the same three (pxfUpper, pxfLower, pxfEnd) and the same target quad at 0xA0: the layout is shared, the fields past it are not. */
struct IKLIMB { int id; int a; int b; int c; u8 unknown_0x10[0x90]; QW q; u8 unknown_0xB0[0x1C]; float f; };
/* local view of the carry object past what carry.h declares (g++ 2.95 starts a derived class's fields at 0x188, after CARRY's 0x184): the two objects the lift's IK limbs follow, read here only */
struct CARRYLIFT : CARRY { u8 unknown_0x188[0x8]; LO *ploLimbA; u8 unknown_0x194[4]; LO *ploLimbB; };
struct GADGETSTATE { u8 unknown_0x0[0x1C]; int flag; };
static inline float Now(const float *pclock) { return *pclock; }
extern "C" {
void func_0012E460(void *);
int func_001A58D0(void *, void *, int);
void SetSoCnstrForce(void *, int);
void SetSoNoXpsAll(void *, int);
float *PeaFindAsegLabel(void *, int);
void PredictXfTransform(int, int, QW *, int, float);
void ConvertAloMat(QW *, void *, int, QW *);
void func_001B72B0(void *, int, void *, QW *, QW *);
int FIsBasicDerivedFrom(void *, int);
void PostGuardStunCommand(void *, void *);
void CalcMurrayThrow(void *, QW, float *, float *, QW *, QW *);
int func_0012DE58(void *, void *, int, QW, QW, float);
QW ConvertXfVec(int, int, QW);
int func_0012DC18(void *, void *, int, int, int, QW);
int func_0012DD28(void *, int, int, void *);
int func_0012DDB0(void *, int, int, int, int, QW *);
void func_00209E88(void *);
void DetachMurrayObject(void *);
void SetMurrayState(void *, int);
extern float RO_002C0A3C, RO_002C0A40;
extern QW RO_002A2D30;
extern float g_2dded0;
void SetMurrayLiftState(MURRAY *self, int state)
{
    if (self->field_0x1450 == state) return;
    if (self->field_0x1450 == 1) {
        func_0012E460(&self->field_0x13FC);
        func_0012E460(&self->field_0x1400);
    }
    self->field_0x1450 = state;
    self->field_0x1454 = Now(&g_2dded0);
    QW sp[8];
    float t;
    switch (state) {
    case 0:
        self->field_0x1448 = 0;
        break;
    case 1: {
        SO *so;
        if (self->ploCarried && (so = ((CARRYLIFT *)self->ploCarried)->pso, ((int)(so->grfo >> 60) & 1))) {
            SetSoCnstrForce(so, 0);
            self->field_0x1404 = so->pxfLinear->kind;
            self->field_0x1408 = so->pxfAngular->kind;
            func_001A58D0(so, 0, 0xF);
            SetSoNoXpsAll(so, 1);
            float *label = PeaFindAsegLabel(((ASEGA *)self->field_0x1030)->paseg, 0x1C7);
            t = (*label - ((ASEGA *)self->field_0x1030)->tLocal) / ((ASEGA *)self->field_0x1030)->svtLocal;
            PredictXfTransform((int)((SO *)self->field_0x13EC)->pxfRoot, (int)self->pxfRoot, sp, 0, t);
            ConvertAloMat(&sp[4], self, 0, sp);
            sp[0] = sp[4]; sp[1] = sp[5]; sp[2] = sp[6]; sp[3] = sp[7];
            func_001B72B0(self, 0, sp, &sp[4], &sp[5]);
            if (FIsBasicDerivedFrom(so, 0x38)) PostGuardStunCommand(so, self);
            CalcMurrayThrow(self, sp[5], label, &t, &sp[6], &sp[7]);
            self->field_0x13FC = func_0012DE58(so, so->pxfLinear, 5, sp[5], sp[7], Now(&g_2dded0) + t);
            so->Slot35(ConvertXfVec((int)so->pxfLinear->pxfParent, 0, sp[6]));
            self->field_0x1400 = func_0012DC18(so, so->pxfAngular, 5, 7, 2, sp[4]);
        } else {
            goto detach;
        }
        break;
    }
    case 2: {
        SO *so;
        if (self->ploCarried == 0 || (so = ((CARRYLIFT *)self->ploCarried)->pso, ((int)(so->grfo >> 60) & 1) == 0)) {
detach:
            DetachMurrayObject(self);
            self->ploCarried = 0;
            SetMurrayState(self, 0);
        } else {
            void *held = (void *)self->field_0x13EC;
            func_001A58D0(so, held, 0xF);
            SetSoNoXpsAll(so, 1);
            func_001B72B0(self, (int)((SO *)held)->pxfRoot, &RO_002A2D30, &sp[1], &sp[0]);
            self->field_0x13F8 = func_0012DC18(so, so->pxfAngular, 5, 7, 2, sp[1]);
            self->field_0x13F4 = func_0012DC18(so, so->pxfLinear, 5, 7, 2, sp[0]);
            LO *a190 = ((CARRYLIFT *)self->ploCarried)->ploLimbA;
            if (a190) {
                IKLIMB *ref = self->pikLimbA;
                ref->id = (int)a190->Slot32(&sp[2]);
                ref->q = sp[5];
                ref->f = RO_002C0A3C;
                self->field_0x1618 = func_0012DD28(self, ref->a, 5, ref);
                self->field_0x161C = func_0012DD28(self, ref->b, 5, ref);
                self->field_0x1604 = func_0012DDB0(self, (int)self->field_0x15F4, 5, 5, ref->id, &sp[2]);
            }
            LO *a198 = ((CARRYLIFT *)self->ploCarried)->ploLimbB;
            if (a198) {
                IKLIMB *ref = self->pikLimbB;
                ref->id = (int)a198->Slot32(&sp[2]);
                ref->q = sp[5];
                ref->f = RO_002C0A40;
                self->field_0x1620 = func_0012DD28(self, ref->a, 5, ref);
                self->field_0x1624 = func_0012DD28(self, ref->b, 5, ref);
                self->field_0x160C = func_0012DDB0(self, (int)self->field_0x15FC, 5, 5, ref->id, &sp[2]);
            }
            if (FIsBasicDerivedFrom(so, 0x38)) func_00209E88(so);
            int *clear = (int *)&self->velGoal;
            clear[2] = 0;
            clear[1] = 0;
            clear[0] = 0;
        }
        break;
    }
    }
    if (self->field_0x1450 < 2) {
        if (self->field_0x1450 >= 0) {
            ((GADGETSTATE *)self->field_0x1088)->flag = 1;
            return;
        }
    }
    ((GADGETSTATE *)self->field_0x1088)->flag = 0;
}
}
