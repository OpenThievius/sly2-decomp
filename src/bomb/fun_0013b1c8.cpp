// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "so.h"
extern "C" int FIsBasicDerivedFrom(BASIC *, void *);
extern "C" void *D_002BC9D0[4];

int func_0013B1C8(int unused, LO *plo)
{
    while (plo) {
        for (unsigned i = 0; i < 4; i++) {
            if (FIsBasicDerivedFrom(plo, D_002BC9D0[i]))
                return 0;
        }
        plo = plo->psoParent;
    }
    return 1;
}
