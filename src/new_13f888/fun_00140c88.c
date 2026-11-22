/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jtview.h"

struct SW;

struct JTVIEW *PpoSwFocusBase(struct SW *psw);
void SetTnTnsOverride(struct TN *ptn, s32 value);
extern struct SW B_003DD490;

void func_00140C88(struct JTVIEW *pjt, struct TN *ptnNew) {
    struct JTVIEW *pjtFocus = PpoSwFocusBase(&B_003DD490);
    struct TN *ptnOld;
    if (pjtFocus == pjt) {
        ptnOld = pjtFocus->ptnOverride;
        if (ptnOld != 0) {
            SetTnTnsOverride(ptnOld, 0);
        }
        pjtFocus->ptnOverride = ptnNew;
        if (ptnNew != 0) {
            SetTnTnsOverride(ptnNew, 1);
        }
    }
}
