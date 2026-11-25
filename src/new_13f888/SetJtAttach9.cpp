/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jt.h"
struct VT_142340 { u8 unknown_0x0[0x2C0]; short delta; short unused; void (*fn)(void *, int, void *); };
struct JTVIEW { u8 unknown_0x0[0xC]; VT_142340 *vt; };
extern "C" void StartAttach(void *, int, void *, int);
extern "C" void SetJtAttach9(JT *pjt, void *ptarget, void *pextra) {
    if (ptarget != 0) {
        StartAttach(pjt->PvAttach(), 9, ptarget, 0);
    } else if (pjt->attachKind == 9) {
        /* slot 88 (JT::SetMode) with a second argument the header does not declare: the call stays a raw vtable call */
        VT_142340 *vt = ((JTVIEW *)pjt)->vt;
        vt->fn((char *)pjt + vt->delta, 0, pextra);
    }
}
