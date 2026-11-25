// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
extern "C" void func_001F2768(SO *so, int flag)
{
    so->field_0xD0 = (so->field_0xD0 & ~0x400000000UL) | ((u64)(flag & 1) << 34);
}
