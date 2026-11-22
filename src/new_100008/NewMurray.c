// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

void *ConstructMurray(void *);

void NewMurray(void)
{
    ConstructMurray(__builtin_new(0x1B00));
}
