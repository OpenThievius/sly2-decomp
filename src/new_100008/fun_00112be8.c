// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

void *Blot_Construct(void *);

void func_00112BE8(void)
{
    Blot_Construct(__builtin_new(0x110));
}
