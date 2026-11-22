/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "dl.h"

void RemoveDlEntry(struct DL *, void *);
void func_001F3E00();
extern struct DL B_003E1450;

void func_001BAD80(void *pentry) {
    func_001F3E00();
    RemoveDlEntry(&B_003E1450, pentry);
}
