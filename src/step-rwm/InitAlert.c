/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "dl.h"
#include "guard.h"

void AppendDlEntry(struct DL *, void *);
extern struct DL B_003E145C;

struct ALERT *InitAlert(struct ALERT *palert, struct LO *palo) {
    palert->palo = palo;
    palert->field_0x14 = 1.0f;
    palert->radCone = 2.0f;
    palert->field_0x10 = -1;
    palert->field_0x8 = -1;
    AppendDlEntry(&B_003E145C, palert);
    return palert;
}
