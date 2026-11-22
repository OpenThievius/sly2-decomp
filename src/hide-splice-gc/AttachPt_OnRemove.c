/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

void RemoveAloHierarchy(struct ATTACHPT *);
void RemoveDlEntry(struct DL *, void *);

void AttachPt_OnRemove(struct ATTACHPT *attach) {
    RemoveAloHierarchy(attach);
    RemoveDlEntry(&B_003E1414, attach);
}
