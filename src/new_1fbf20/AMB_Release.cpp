// SPDX-License-Identifier: GPL-3.0-or-later
#include "amb.h"
extern "C" {
extern void BASIC_Destruct(AMB *, int);
extern int FreeAmb(AMB *);

void AMB_Release(AMB *pamb) {
    int cRef;

    cRef = pamb->cRef - 1;
    pamb->cRef = cRef;
    if (((cRef << 0x10) == 0) && (pamb != 0)) {
        BASIC_Destruct(pamb, 0);
        FreeAmb(pamb);
    }
}
}
