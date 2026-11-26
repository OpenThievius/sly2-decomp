// SPDX-License-Identifier: GPL-3.0-or-later
#include "mount.h"
#include "sly2.h"
#include "xf.h"
#include "blot.h"
#include "amb.h"
extern "C" {
extern char B_002DEB30;
extern QW g_2a2dd0;
void ConvertXfMatrix4(MATRIX4 *, XF *, XF *, void *);
QW DecomposeRotateMatrixEuler(void *);
void Mount_UpdateHealthBlot(MOUNT *);
AMB *NewEmitter(int);
void PauseAmb(AMB *);
void SetEmitterUnpositioned(AMB *, LO *);
void SetSmaGoal__FP3SMA3OID(void *, int);
void SetSoCnstrForce(MOUNT *, int);
void SetSoCnstrTorque(MOUNT *, int);
void SetXfKind(MOUNT *, XF *, int);
void StopAmb(AMB *, float);
void VirtualRefPtr_Assign(AMB **, AMB *);
void bevy_camera_follow_activity(void *, int, MOUNT *);
int func_0012DC18(MOUNT *, XF *, int, int, int, QW);
void func_0012E460(int *);
void func_0017F4C0(MOUNT *, ANIMENTRY *);
void func_001A58D0(MOUNT *, int, int);
void func_001F68A8(MOUNT *, int);
void func_00213B00(BLOT *, int);
}

// Retail reads the state at 0x1C0 and stores the new one there, then the clock time at
// 0x1C4 and the per-state slots from 0x1C8 (sll 4 + 0x1C8), so state/timer sit together
// before the slots. The clock global 0x2DDED0 is read as the first float of a struct
// (time, dt) as in SetBentleyState: as a plain float, gcc hoists its lwc1 above the state
// store into every branch delay slot; a struct member load keeps retail's order
// (sw state, then lwc1 time).
extern "C" void Mount_SetState(MOUNT *self, int newState)
{
    int stateOld = self->state;
    if (newState == stateOld)
        return;
    switch (stateOld) {
    case -1: {
        BLOT *pblot = (BLOT *)self->pblot;
        if (pblot != 0) {
            pblot->Select(-1);
            func_00213B00((BLOT *)self->pblot, 0x34F);
            Mount_UpdateHealthBlot(self);
            if (self->field_0x2A8 != -1) {
                AMB *pamb = NewEmitter(self->field_0x2A8);
                SetEmitterUnpositioned(pamb, 0);
                VirtualRefPtr_Assign(&self->pamb, pamb);
                PauseAmb(self->pamb);
            }
        }
        break;
    }
    case 3:
        func_0012E460(&self->hActA);
        func_0012E460(&self->hActB);
        SetXfKind(self, self->pxfLinear, 2);
        SetXfKind(self, self->pxfAngular, 2);
        func_001A58D0(self, 0, 0xF);
        SetSoCnstrForce(self, 5);
        SetSoCnstrTorque(self, 4);
        func_001F68A8(self, 0);
        self->ploAttach = 0;
        break;
    case 1: {
        int index = 0;
        if (self->crec > 0) {
            void **ppsma = &self->arec[0].psma;
            do {
                if (*ppsma != 0)
                    SetSmaGoal__FP3SMA3OID(*ppsma, 0x66);
                index += 1;
                ppsma += 6;
            } while (index < self->crec);
        }
        break;
    }
    }
    self->state = newState;
    self->tState = g_2dded0.t;
    switch (newState) {
    case -1: {
        BLOT *pblot = (BLOT *)self->pblot;
        if (pblot != 0)
            pblot->Hide();
        AMB **ppamb = &self->pamb;
        if (*ppamb != 0) {
            StopAmb(*ppamb, 0.0f);
            VirtualRefPtr_Assign(ppamb, 0);
        }
        break;
    }
    case 3: {
        MATRIX4 world;
        MATRIX4 matrix;
        void *handle = self->ploAttach->Slot32(&world);
        ConvertXfMatrix4(&matrix, self->axf->pxfParent, self->pxfLinear->pxfParent, &world);
        world = matrix;
        self->SetParent(self->ploAttach->psoParent, handle, 3);
        self->Slot35(g_2a2dd0);
        self->Slot36(g_2a2dd0);
        self->hActA = func_0012DC18(self, self->pxfLinear, 1, 7, 2, *(QW *)&world.mat[3][0]);
        QW euler = DecomposeRotateMatrixEuler(&world);
        self->hActB = func_0012DC18(self, self->pxfAngular, 1, 7, 2, euler);
        SetSoCnstrForce(self, 1);
        SetSoCnstrTorque(self, 1);
        func_001F68A8(self, 1);
        break;
    }
    case 4:
        bevy_camera_follow_activity(&B_002DEB30, 0x10, self);
        break;
    }
    func_0017F4C0(self, newState != -1 ? &self->aentry[newState] : 0);
}
