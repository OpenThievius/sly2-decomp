// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

void *ConstructGuard(void *);

void NewGuard(void)
{
    ConstructGuard(__builtin_new(0x1010));
}
