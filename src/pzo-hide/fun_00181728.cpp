// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"

extern "C" void Mount_SetState(MOUNT *, int);

extern "C" void func_00181728(GRAB *grab)
{
    Mount_SetState(grab->pmount, 1);
    grab->pmount = 0;
    grab->HandleSpliceEvent(6, 0, 0, 0, 0);
}
