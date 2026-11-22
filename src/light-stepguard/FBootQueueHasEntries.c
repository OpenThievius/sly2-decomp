/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "bootq.h"

s32 FBootQueueHasEntries(struct BOOTQ *pbootq) {
    return pbootq->iEntryNext < pbootq->cEntry;
}
