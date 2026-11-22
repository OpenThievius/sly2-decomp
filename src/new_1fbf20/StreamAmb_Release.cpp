// SPDX-License-Identifier: GPL-3.0-or-later
#include "amb.h"
extern "C" {
void BASIC_Destruct(AMB *, s32);
void FreeStreamAmb(AMB *);

void StreamAmb_Release(AMB *pamb) {
    s32 cRef = pamb->cRef - 1;

    pamb->cRef = (u16)cRef;
    if ((cRef << 16) == 0 && pamb != 0) {
        BASIC_Destruct(pamb, 0);
        FreeStreamAmb(pamb);
    }
}

}
