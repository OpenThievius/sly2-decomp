// SPDX-License-Identifier: GPL-3.0-or-later
#include "amb.h"

extern "C" void SetAmbGrf(AMB *pamb, int grfMask, int grfValue);

struct AMBREF {
    AMB *pamb;
    AMBREF(AMB *target) { pamb = target; pamb->AddRef(); }
    ~AMBREF() { pamb->Release(); }
};

extern "C" void UpdateAmb(AMB *pamb)
{
    AMBREF ref(pamb);
    if (pamb->grf & 0x200)
        pamb->Slot16();
    else
        pamb->volAudible = pamb->volume;
    unsigned short grf = pamb->grf;
    if (grf & 1) {
        pamb->Slot9();
        if (pamb->Slot8() == 1)
            SetAmbGrf(pamb, 0x400, 0x400);
    } else if (pamb->voice != 0) {
        if (grf & 8) {
            pamb->Slot10();
            pamb->voice = 0;
            SetAmbGrf(pamb, 0x1DFF, 0);
        } else {
            if (grf & 0x1C00)
                pamb->Slot14();
            if (pamb->fPending != 0)
                return;
            if (pamb->grf & 0x1F0) {
                pamb->Slot13();
                SetAmbGrf(pamb, 0x1F0, 0);
            }
            grf = pamb->grf;
            if (grf & 2) {
                pamb->Slot11();
                SetAmbGrf(pamb, 2, 0);
            } else if (grf & 4) {
                pamb->Slot12();
                SetAmbGrf(pamb, 4, 0);
            }
        }
    } else if (pamb->fPending == 0 && !(grf & 0x200)) {
        SetAmbGrf(pamb, 0x1FFF, 0);
    }
}
