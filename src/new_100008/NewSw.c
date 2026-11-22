// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

void *Sw_Construct(void *);

void NewSw(void)
{
    Sw_Construct(__builtin_new(0x4790));
}
