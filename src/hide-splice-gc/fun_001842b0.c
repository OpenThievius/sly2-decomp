/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

void *PloFindSwObject_thunk(void *, int, int, void *);
void func_00183F50(struct LIFTPT *);
extern char B_003DD490[];

void func_001842B0(struct LIFTPT *lift) {
    func_00183F50(lift);
    lift->aref[0].plo = PloFindSwObject_thunk(B_003DD490, 4, lift->aref[0].oid, lift);
    lift->aref[1].plo = PloFindSwObject_thunk(B_003DD490, 4, lift->aref[1].oid, lift);
    lift->aref[2].plo = PloFindSwObject_thunk(B_003DD490, 4, lift->aref[2].oid, lift);
}
