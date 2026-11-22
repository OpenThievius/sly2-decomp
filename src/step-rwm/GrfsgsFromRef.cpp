// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
extern "C" {
/* the 16-byte result slot func_002013D8 fills is the frame's, as retail has it (cref.h's CRef is 8 bytes) */
struct REFSLOT {
    u8 unknown_0x0[0x10];
};
void CRef_Destruct(REFSLOT *);
s32 GrfsgsFromAsgs(s32, s32 *);
REFSLOT *func_002013D8(REFSLOT *, s32, s32, s32, s32 *, s32 *);
s32 GrfsgsFromRef(s32 refList) {
    s32 asgs[0x10] __attribute__((aligned(16)));
    REFSLOT ref __attribute__((aligned(16)));
    s32 casgs;
    s32 grfsgs;
    func_002013D8(&ref, refList, 0x1010, 0x10, &casgs, asgs);
    grfsgs = GrfsgsFromAsgs(casgs, asgs);
    CRef_Destruct(&ref);
    return grfsgs;
}
}
