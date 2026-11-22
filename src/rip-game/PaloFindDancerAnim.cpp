// SPDX-License-Identifier: GPL-3.0-or-later
#include "dancer.h"
extern "C" {
extern char B_003DD490[];
LO *PloFindSwObject_thunk(char *sw, s32 kind, s32 oid, DANCER *dancerContext);

LO *PaloFindDancerAnim(DANCER *dancer, s32 oid) {
    LO *found = PloFindSwObject_thunk(B_003DD490, 4, oid, dancer);
    if (found != 0) {
        found->Remove();
    }
    return found;
}

}
