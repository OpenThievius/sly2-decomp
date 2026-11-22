/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

void RemoveAloHierarchy(void *);
void RemoveDlEntry(struct DL *, void *);

void AttachFlat_OnRemove(struct ATTACHFLAT *attach) {
    RemoveAloHierarchy(attach);
    RemoveDlEntry(&B_003E1408, attach);
}
