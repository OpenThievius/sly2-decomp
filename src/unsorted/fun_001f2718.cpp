// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
void func_001F2718(SO *so, int value)
{
    so->grfso = (so->grfso & ~0xF00000UL) | ((value & 0xF) << 20);
}
