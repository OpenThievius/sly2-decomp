// SPDX-License-Identifier: GPL-3.0-or-later
#include "po.h"

// PO slot 81: posts splice event 12 with the addresses of its two arguments (SetDprizeCharmDprizes passes the heal range)
extern "C" void func_001C4228(PO *ppo, int first, int second)
{
    int *args[2];
    args[0] = &first;
    args[1] = &second;
    ppo->HandleSpliceEvent(12, 0, 2, (sptr)args, 0);
}
