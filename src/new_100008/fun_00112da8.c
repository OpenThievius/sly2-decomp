// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

void *CM_Construct(void *);

void func_00112DA8(void)
{
    CM_Construct(__builtin_new(0x630));
}
