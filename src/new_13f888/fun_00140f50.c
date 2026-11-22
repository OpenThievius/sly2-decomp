/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jtview.h"

void ZapTakeDamage(void *pvZap);

void func_00140F50(struct JTVIEW *pjt) {
    ZapTakeDamage(pjt->zap);
}
