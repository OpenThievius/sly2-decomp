/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "dl.h"

void AppendDlEntry(struct DL *, void *);
void func_001F3EA8();
extern struct DL B_003E1450;

void func_001BADB8(void *pentry) {
    func_001F3EA8();
    AppendDlEntry(&B_003E1450, pentry);
}
