// SPDX-License-Identifier: GPL-3.0-or-later
#include "amb.h"
#include "lo.h"
#include "sly2.h"
extern "C" {
void StopAmb(AMB *, float);
}
QW ConvertAloPos(LO *, int, QW);
void CalculateVolPan(AMB *, QW, void *, float *, int *);
void SetAmbPan(AMB *, int);
void SetAmbGrf(AMB *, int, int);
void UpdateAmbPositional(AMB *pamb)
{
    LO *palo = pamb->palo;
    if (palo != 0 && ((palo->grfo >> 60) & 1) == 0) {
        StopAmb(pamb, 0.0f);
        return;
    }
    QW world = ConvertAloPos(pamb->palo, 0, pamb->pos);
    float falloff;
    int degrees;
    CalculateVolPan(pamb, world, &pamb->lmMin, &falloff, &degrees);
    float audible = pamb->volume * falloff;
    if ((int)(audible * 1024.0f) != (int)(pamb->volAudible * 1024.0f)) {
        if (pamb->volAudible == 0.0f) {
            pamb->Slot15(0);
        } else if (audible == 0.0f) {
            pamb->Slot15(1);
        }
        pamb->volAudible = audible;
        SetAmbGrf(pamb, 0x10, 0x10);
    }
    SetAmbPan(pamb, degrees);
}
