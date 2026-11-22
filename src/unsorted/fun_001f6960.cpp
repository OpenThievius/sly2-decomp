// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
int func_001F6960(SO *pso)
{
    return (int)((pso->grfso << 6) >> 32) & 1;
}
