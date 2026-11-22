// SPDX-License-Identifier: GPL-3.0-or-later
#include "crv.h"
extern "C" {

void CloneXfm(LO *);
void *PattachCrv(CRV *, s32);

void CloneCrv(CRV *crv) {
    CloneXfm(crv);
    if (crv->pattach != 0) {
        crv->pattach = 0;
        PattachCrv(crv, 0);
    }
}
}
