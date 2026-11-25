// SPDX-License-Identifier: GPL-3.0-or-later
#include "wipe.h"
struct MSGARGS { int unk0; int unk4; int msg; };
extern "C" void HandleLoMessage(WIPE *, int, MSGARGS *);
extern "C" void SetWipeState(WIPE *, int);

void HandleWipeMessage(WIPE *wipe, int msgid, MSGARGS *args)
{
    HandleLoMessage(wipe, msgid, args);
    if (msgid != 9) return;
    if (args->unk0 != (int)wipe->pasega) return;
    switch (args->msg) {
    case 0x5FB: wipe->field_0x164 = 1; break;
    case 0x5FC: wipe->field_0x164 = 0; break;
    case 0x5FD: wipe->field_0x168 = 1; break;
    case 0x5FE: wipe->field_0x168 = 0; break;
    case 0x5FF: wipe->field_0x16C = 0; break;
    case 0x600: wipe->field_0x16C = 1; break;
    case 0x601:
        if (wipe->hstream != -1) SetWipeState(wipe, 3);
        break;
    }
}
