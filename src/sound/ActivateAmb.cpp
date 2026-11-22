// SPDX-License-Identifier: GPL-3.0-or-later
#include "amb.h"
extern "C" {
int FFindDlEntry(DL *, void *);
void AppendDlEntry(DL *, void *);
extern DL B_003DD08C;

void ActivateAmb(AMB *pamb)
{
    if (FFindDlEntry(&B_003DD08C, pamb) == 0) {
        pamb->AddRef();
        AppendDlEntry(&B_003DD08C, pamb);
    }
}
}
