// SPDX-License-Identifier: GPL-3.0-or-later
#include "jt.h"

/* JT's word at 0x9C0, which func_0018DE18 sets when it attaches (one reader, not a method of the class): a view of JT */
struct JTATTACHVIEW {
    u8 unknown_0x0[0x9C0];
    /* 0x9C0 */ s32 field_0x9C0;
};

extern "C" void StartAttach(void *, int, LO *, int);

extern "C" void func_0018DE18(JT *pjt, LO *plo) {
    if (plo != 0) {
        ((JTATTACHVIEW *)pjt)->field_0x9C0 = 1;
        StartAttach(pjt->PvAttach(), 6, plo, 0);
    } else if (pjt->attachKind == 6) {
        pjt->SetMode(0);
    }
}
