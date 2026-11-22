/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

void func_001A6178(struct ATTACHZONE *);
void AppendDlEntry(struct DL *, void *);

void AttachZone_OnAdd(struct ATTACHZONE *attach) {
    func_001A6178(attach);
    AppendDlEntry(&B_003E1438, attach);
}
