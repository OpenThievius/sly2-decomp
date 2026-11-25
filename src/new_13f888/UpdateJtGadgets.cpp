// SPDX-License-Identifier: GPL-3.0-or-later
#include "jt.h"
#include "joy.h"
/* a gadget slot as UpdateJtGadgets reads it: GADGETSLOT's word at 4 is the slot's state here (jt.h declares it as the pool pointer UseSlyGadget leases from) */
struct SLOT141A50 { int id; int state; int unknown_0x8; };
struct GADGETDEF141A50 { int id; int unknown_0x4; int unknown_0x8; int power; u8 unknown_0xC[0x10]; };
extern "C" {
int FButtonPressedWithin(JOY *, int, float);
int GetJtPower(JT *);
void *NewEmitter(int);
void SetEmitterUnpositioned(void *, int);
void SetJtGadgetSlotState(JT *, SLOT141A50 *, int);
extern GADGETDEF141A50 D_002BCD00[];
extern int D_002C3258[];
extern float g_2dded0;
void UpdateJtGadgets(JT *self)
{
    if (self->pjoy) {
        for (int index = 0; index < 3; index++) {
            int button = D_002C3258[index];
            SLOT141A50 *slot = (SLOT141A50 *)&self->aslot[index];
            int gadget = slot->id;
            switch (slot->state) {
            case 0:
                if (FButtonPressedWithin(self->pjoy, button, 0.15f)) {
                    if (!self->FCanUseGadget(gadget)) {
                        SetEmitterUnpositioned(NewEmitter(0x2E), 0);
                    } else if (GetJtPower(self) < D_002BCD00[gadget].power) {
                        SetEmitterUnpositioned(NewEmitter(0x2E), 0);
                        self->field_0x1304 = g_2dded0;
                    } else {
                        SetJtGadgetSlotState(self, slot, D_002BCD00[gadget].id);
                    }
                }
                break;
            case 1:
                if (!((self->pjoy->grfbtn & button) && self->FCanUseGadget(gadget))) {
                    SetJtGadgetSlotState(self, slot, 0);
                } else {
                    self->DrainGadget(slot);
                }
                break;
            }
        }
    }
}
}
