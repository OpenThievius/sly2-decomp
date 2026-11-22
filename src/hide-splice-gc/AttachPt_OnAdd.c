/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

void func_001A6178(struct ATTACHPT *);
void AppendDlEntry(struct DL *, void *);

void AttachPt_OnAdd(struct ATTACHPT *attach) {
    func_001A6178(attach);
    AppendDlEntry(&B_003E1414, attach);
}
