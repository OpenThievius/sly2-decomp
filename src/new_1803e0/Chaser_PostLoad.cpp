// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"
#include "so.h"
#include "xf.h"
#include "crv.h"
extern "C" {
CRV *PcrvNew(s32 oid, s32 ccv);                      /* extern */
void SetXfKind(SO *pso, XF *pxf, s32 kind);          /* extern */
void func_0017F138(CHASER *pchaser);                 /* extern */
void func_0017F408(LO *ploContext, s32 centry, ANIMENTRY *aentry); /* extern */

void Chaser_PostLoad(CHASER *pchaser) {
    func_0017F138(pchaser);
    pchaser->pcrv = PcrvNew(0x2C9, 0x10);
    if (pchaser->pxfLinear != 0) {
        SetXfKind(pchaser, pchaser->pxfLinear, 2);
    }
    if (pchaser->pxfAngular != 0) {
        SetXfKind(pchaser, pchaser->pxfAngular, 2);
    }
    func_0017F408(pchaser, 5, pchaser->aentry);
}

}
