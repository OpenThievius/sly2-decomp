// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
struct ENTRY {
    int key;
    char pad[0x24];
};
extern "C" ENTRY *func_001F5FF8(SO *so, int key)
{
    for (int index = 0; index < so->field_0xB8; index++) {
        if (((ENTRY *)so->field_0xC0)[index].key == key)
            return &((ENTRY *)so->field_0xC0)[index];
    }
    return 0;
}
