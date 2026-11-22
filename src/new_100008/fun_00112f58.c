// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

void *InitJumper(void *);

void func_00112F58(void)
{
    InitJumper(__builtin_new(0x70));
}
