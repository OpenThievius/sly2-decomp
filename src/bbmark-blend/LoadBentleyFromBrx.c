/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "soproperty.h"

void LoadStepFromBrx(void *pbentley);
void SetSoProperties(void *pso, s32 count, const SOPROPERTY *pproperties);
extern SOPROPERTY D_002BC390[];

void LoadBentleyFromBrx(void *pbentley) {
    LoadStepFromBrx(pbentley);
    SetSoProperties(pbentley, 0x76, D_002BC390);
}
