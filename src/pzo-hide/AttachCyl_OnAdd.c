/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

void func_001A6178(void *);
void AppendDlEntry(struct DL *, void *);

void AttachCyl_OnAdd(struct ATTACHCYL *attach) {
    func_001A6178(attach);
    AppendDlEntry(&B_003E13FC, attach);
}
