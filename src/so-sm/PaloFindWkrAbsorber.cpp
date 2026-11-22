// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "so.h"
extern "C" {
s32 GrficFromAlo(LO *, s32);

LO *PaloFindWkrAbsorber(LO *palo, s32 grftak) {
    LO *current;

    current = palo;
    while (current != 0) {
        if (GrficFromAlo(current, grftak) != 0) {
            return current;
        }
        current = current->psoParent;
    }
    return 0;
}

}
