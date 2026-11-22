/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "crv.h"
#include "dl.h"

void RemoveAloHierarchy(struct CRV *crv);
void RemoveDlEntry(struct DL *, void *);
extern struct DL B_003E13C0;

void RemoveCrv(struct CRV *crv) {
    RemoveAloHierarchy(crv);
    RemoveDlEntry(&B_003E13C0, crv);
}
