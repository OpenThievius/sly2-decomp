// SPDX-License-Identifier: GPL-3.0-or-later
#include "swfind.h"

/* a Dcb option that names a world object: where to store it and which object id to look up */
struct DCBOPTION {
    /* 0x00 */ s32 oid;
    /* 0x04 */ s32 offset;
};

extern "C" {
extern SW B_003DD490; /* the world */
void DcbSetOptionPlo(LO *plo, DCBOPTION *poption) {
    *(LO **)((char *)plo + poption->offset) = PloFindSwObject_thunk(&B_003DD490, 4, poption->oid, plo);
}
}
