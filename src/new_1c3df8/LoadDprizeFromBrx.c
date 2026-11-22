/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "xf.h"
#include "soproperty.h"
#include "soview.h"

struct BIS;

/* the object func_001F7B98 finds or creates (oid 0x187, class 0x12) and returns; its own source declares it void, but retail's
   caller stores through $v0 right after the call */
struct PLO0X187 {
    u8 unknown_0x0[0xF0];
    /* 0xF0 */ s32 field_0xF0;
};

void CSo_LoadFromBrx(struct SOVIEW *pso, struct BIS *pbis);              /* extern */
void SetSoProperties(struct SOVIEW *pso, s32 cprop, SOPROPERTY *aprop); /* extern */
void SetXfKind(struct SOVIEW *pso, struct XF *pxf, s32 kind);           /* extern */
struct PLO0X187 *func_001F7B98(struct SOVIEW *pso);                     /* extern */
extern SOPROPERTY D_002C0D40[];

void LoadDprizeFromBrx(struct SOVIEW *pso, struct BIS *pbis) {
    CSo_LoadFromBrx(pso, pbis);
    func_001F7B98(pso)->field_0xF0 = 1;
    SetXfKind(pso, pso->pxfLinear, 0x15);
    SetXfKind(pso, pso->pxfAngular, 0x15);
    SetSoProperties(pso, 1, D_002C0D40);
}
