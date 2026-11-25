// SPDX-License-Identifier: GPL-3.0-or-later
#include "bentley.h"
struct ACT { u8 unknown_0x0[0x148]; u64 flags; };
/* what the player stands on, as func_001942F0 reads it (STEP::psoSurface is declared a SO, its fields are those of a geometry) */
struct SURFACE { u8 unknown_0x0[0x40]; int field_0x40; u8 unknown_0x44[8]; ACT *act; u8 unknown_0x50[0x10]; QW pos; u8 unknown_0x70[0x18]; float field_0x88; };
extern "C" void AddSafePointOnGeom(void *, int, QW);
extern "C" void func_001942F0(void *);
extern "C" void UpdateJtPipeLook(void *);

void func_00135EB0(BENTLEY *pbentley)
{
    switch (pbentley->state) {
    case 0: case 1: case 5: case 6: case 7: case 11: case 12: case 14: {
        SURFACE *psurface = (SURFACE *)pbentley->psoSurface;
        if (psurface) {
            float level = psurface->field_0x88;
            if (0.7f < level) {
                if (!(psurface->act->flags & 0x20000000UL)) {
                    if (pbentley->field_0x108C == 0)
                        AddSafePointOnGeom(pbentley->PvPart9E0(), psurface->field_0x40, psurface->pos);
                }
            }
        }
        break;
    }
    case 3:
        func_001942F0(pbentley->PvAttach());
        break;
    case 13:
        UpdateJtPipeLook(pbentley->PvPipe());
        break;
    }
}
