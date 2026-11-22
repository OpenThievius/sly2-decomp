/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "crv.h"
#include "dl.h"

void func_001A6178(struct CRV *crv);
void AppendDlEntry(struct DL *, void *);
extern struct DL B_003E13C0;

void AddCrv(struct CRV *crv) {
    func_001A6178(crv);
    AppendDlEntry(&B_003E13C0, crv);
}
