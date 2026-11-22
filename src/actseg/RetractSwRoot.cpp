// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"

extern "C" {
void RemoveDlEntry(DL *, void *);
void AppendDlEntry(DL *, void *);

void RetractSwRoot(SW *psw, void *proot)
{
    RemoveDlEntry(&psw->dlRoot, proot);
    if (psw->field_0x39A4 == 0) {
        psw->field_0x39A4 = proot;
    }
    AppendDlEntry(&psw->dlRoot, proot);
}
}
