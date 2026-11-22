/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

void RemoveAloHierarchy(void *);
void RemoveDlEntry(struct DL *, void *);

void AttachCyl_OnRemove(struct ATTACHCYL *attach) {
    RemoveAloHierarchy(attach);
    RemoveDlEntry(&B_003E13FC, attach);
}
