// SPDX-License-Identifier: GPL-3.0-or-later
#include "streamamb.h"
struct B8 { char b[8]; };
extern "C" void SetAmbGrf(AMB *, int, int);
void AddAmbSlotSource(STREAMAMB *amb, unsigned slot, int palo, const B8 *range, float vol)
{
    if (slot < 6) {
        if (amb->count[slot] < 8) {
            SetAmbGrf(amb, 0x200, 0x200);
            AMBSLOTSOURCE *src = &amb->src[slot][amb->count[slot]++];
            src->palo = palo;
            src->vol = vol;
            *(B8 *)&src->lmMin = *range;
            float a = src->lmMin;
            float b = src->lmMax;
            if (a == b)
                src->lmMax = b + 1.0f;
        }
    }
}
