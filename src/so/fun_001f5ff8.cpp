// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
extern "C" GLOBENTRY *func_001F5FF8(SO *so, int key)
{
    for (int index = 0; index < so->field_0xB8; index++) {
        if (so->field_0xC0[index].oid == key)
            return &so->field_0xC0[index];
    }
    return 0;
}
