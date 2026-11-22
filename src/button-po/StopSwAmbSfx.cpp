// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
#include "amb.h"
extern "C" {
void StopAmb(AMB *pamb, float seconds);
void VirtualRefPtr_Assign(AMB **ppamb, AMB *pamb);
void StopSwAmbSfx(SW *psw, int sfxid, int iUnused, AMB **ppambRef) {
    AMB *pamb = *ppambRef;
    if (pamb != 0 && (sfxid == -1 || pamb->sfxid == sfxid)) {
        StopAmb(pamb, 0.0f);
        VirtualRefPtr_Assign(ppambRef, 0);
    }
}
}
