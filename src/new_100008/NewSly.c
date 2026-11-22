// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

void *ConstructSly(void *);

void NewSly(void)
{
    ConstructSly(__builtin_new(0x2060));
}
