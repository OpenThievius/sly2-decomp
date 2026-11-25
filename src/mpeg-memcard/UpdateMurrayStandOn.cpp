// SPDX-License-Identifier: GPL-3.0-or-later
#include "murray.h"
#include "so.h"
/* What the player stands on (STEP::psoSurface holds it, typed SO there): a contact record, not an SO. Its object at 0x4C is an SO
   (its grfso is at 0x148); the 0.7 test is on the z lane at 0x88, as the contact normal of AdjustMurrayNewXp. */
struct STANDCONTACT {
    u8 unknown_0x0[0x40];
    s32 field_0x40;
    u8 unknown_0x44[0x8];
    SO *pso;
    u8 unknown_0x50[0x10];
    QW pos;
    u8 unknown_0x70[0x18];
    f32 nz;
};
/* The word of the player at 0x108C that UpdateMurrayStandOn tests (jt.h has it inside an unknown span). */
struct MURRAYSTANDVIEW {
    u8 unknown_0x0[0x108C];
    s32 field_0x108C;
};
extern "C" void AddSafePointOnGeom(void *, int, QW);
extern "C" void func_001942F0(void *);
extern "C" void UpdateJtPipeLook(void *);

extern "C" void UpdateMurrayStandOn(MURRAY *self)
{
    switch (self->state) {
    case 0: case 1: case 4: case 5: case 7: case 8: case 9: case 10: case 18: case 21: {
        STANDCONTACT *pcontact = (STANDCONTACT *)self->psoSurface;
        if (pcontact) {
            float level = pcontact->nz;
            if (0.7f < level) {
                if (!(pcontact->pso->grfso & 0x20000000UL)) {
                    if (((MURRAYSTANDVIEW *)self)->field_0x108C == 0)
                        AddSafePointOnGeom(self->PvPart9E0(), pcontact->field_0x40, pcontact->pos);
                }
            }
        }
        break;
    }
    case 13:
        func_001942F0(self->PvAttach());
        break;
    case 20:
        UpdateJtPipeLook(self->PvPipe());
        break;
    }
}
