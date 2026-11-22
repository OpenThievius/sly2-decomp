// SPDX-License-Identifier: GPL-3.0-or-later
#include "joy.h"
extern "C" {
void AppendSlEntry(void *, JOY *);
void ResetVjoy(JOY *);
extern char B_003E133C;
extern char D_002CA240;

JOY *VJOY_constructor(JOY *pjoy, s32 arg1) {
    pjoy->field_0x0 = 0;
    pjoy->field_0x4 = 0;
    pjoy->pvtbl = &D_002CA240;
    ResetVjoy(pjoy);
    pjoy->vjoym = -1;
    pjoy->field_0x7C = arg1;
    AppendSlEntry(&B_003E133C, pjoy);
    return pjoy;
}
}
