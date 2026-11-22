/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct ASEG;

/* the part of SLOTSO (slotso.h, C++ only) this function reads; same offsets */
struct SLOTSOVIEW {
    u8 unknown_0x0[0x17C];
    struct {
        s32 oid;
        struct ASEG *paseg;
        s32 def;
    } aslot[6];
    u8 unknown_0x1C4[0x8];
    f32 field_0x1CC;
    f32 field_0x1D0;
};

void GSpeedSlotSoAseg(struct SLOTSOVIEW *pso, struct ASEG *paseg, f32 *pgSpeed);
void PostSoLoad(struct SLOTSOVIEW *pso);
void ResolveSlotSoAsegs(struct SLOTSOVIEW *pso);
void func_001B0D90(struct SLOTSOVIEW *pso);

void func_001B0D08(struct SLOTSOVIEW *pso) {
    PostSoLoad(pso);
    ResolveSlotSoAsegs(pso);
    GSpeedSlotSoAseg(pso, pso->aslot[1].paseg, &pso->field_0x1CC);
    GSpeedSlotSoAseg(pso, pso->aslot[4].paseg, &pso->field_0x1D0);
    func_001B0D90(pso);
}
