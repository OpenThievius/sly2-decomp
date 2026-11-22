// SPDX-License-Identifier: GPL-3.0-or-later
#include "attach.h"
#include "jmp.h"
#include "vu0inline.h"
#include "ps2inline.h"
/* the target of an attach as func_001942F0 reads it: by class 0xC, 0x22 or 0x26 */
struct TARGETVIEW { u8 unknown_0x0[0xEC]; int unkEC; u8 unknown_0xF0[0x1C]; float unk10C; u8 unknown_0x110[0x74]; float unk184; u8 unknown_0x188[0x14]; int unk19C; };
static inline TARGETVIEW *TargetOf(ATTACH *pattach) { return (TARGETVIEW *)pattach->ptarget; }
extern "C" int FIsBasicDerivedFrom(void *, int);
extern "C" QW PosLoWorld(void *);
extern "C" float atan2f(float, float);
extern "C" void AddSafePointOnMember(void *, int, float);
extern "C" void AddSafePointOnGeom(void *, int, QW);
union QUADVECTOR { QW quad; float lane[4]; };
void func_001942F0(ATTACH *pattach)
{
    switch (pattach->kind) {
    case 3:
        if (TargetOf(pattach)->unk19C != 0)
            return;
        AddSafePointOnMember(pattach->pjt->PvPart9E0(), pattach->imember, pattach->value);
        break;
    case 4:
        if (TargetOf(pattach)->unkEC != 0)
            return;
        AddSafePointOnMember(pattach->pjt->PvPart9E0(), pattach->imember, 0.0f);
        break;
    case 0:
    case 13:
        if (FIsBasicDerivedFrom(pattach->ptarget, 0xC)) {
            if (TargetOf(pattach)->unk19C != 0)
                return;
            AddSafePointOnMember(pattach->pjt->PvPart9E0(), pattach->imember, pattach->value);
        } else if (FIsBasicDerivedFrom(pattach->ptarget, 0x26)) {
            if (TargetOf(pattach)->unkEC != 0)
                return;
            AddSafePointOnMember(pattach->pjt->PvPart9E0(), pattach->imember, 0.0f);
        } else {
            float scale;
            if (FIsBasicDerivedFrom(pattach->ptarget, 0x22)) {
                if (TargetOf(pattach)->unkEC != 0)
                    return;
                scale = TargetOf(pattach)->unk10C;
            } else {
                scale = TargetOf(pattach)->unk184;
            }
            QW ownerPosition = PosLoWorld(pattach->pjt);
            QW targetPosition = PosLoWorld(pattach->ptarget);
            QUADVECTOR difference;
            difference.quad = VectorSub(ownerPosition, targetPosition);
            float angle = atan2f(difference.lane[1], difference.lane[0]) * scale;
            AddSafePointOnMember(pattach->pjt->PvPart9E0(), pattach->imember, angle);
        }
        break;
    default: {
        SURFACE *psurface = (SURFACE *)pattach->pjt->psoSurface;
        if (psurface) {
            float level = psurface->unk88;
            if (0.7f < level) {
                if (!(psurface->act->flags & 0x20000000UL)) {
                    if (pattach->pjt->field_0x108C == 0)
                        AddSafePointOnGeom(pattach->pjt->PvPart9E0(), psurface->unk40, psurface->pos);
                }
            }
        }
        break;
    }
    }
}
