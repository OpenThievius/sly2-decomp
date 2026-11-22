/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "button.h"

/* oid and nArg go straight through to FAddAshOid: retail's wrapper leaves $a1 and $a2 alone */
void AddBtnOffAseg(struct BTN *pbtn, s32 oid, s32 nArg) {
    FAddAshOid(&pbtn->ashOff, oid, nArg);
}
