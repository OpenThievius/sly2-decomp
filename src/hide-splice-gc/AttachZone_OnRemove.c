/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

void RemoveAloHierarchy(struct ATTACHZONE *);
void RemoveDlEntry(struct DL *, void *);

void AttachZone_OnRemove(struct ATTACHZONE *attach) {
    RemoveAloHierarchy(attach);
    RemoveDlEntry(&B_003E1438, attach);
}
