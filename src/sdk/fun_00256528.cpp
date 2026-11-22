/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sl.h"
struct LISTNODE {
    s32 serial;
};
struct LISTHEAD {
    LISTNODE *first;
    u8 unknown_0x4[0x24];
    SL cursors; /* 0x28, every cursor opened on the list */
};
struct LISTCURSOR {
    LISTNODE *node;
    u8 unknown_0x4[0x8];
    LISTHEAD *list; /* 0x0C */
    s32 position;   /* 0x10 */
    u8 unknown_0x14[0xC];
    s32 serial;     /* 0x20, the node's serial when the cursor was opened */
};
extern "C" {
void AppendSlEntry(SL *list, void *entry);

void func_00256528(LISTCURSOR *cursor, LISTHEAD *list, s32 position) {
    cursor->node = list->first;
    cursor->position = position;
    cursor->list = list;
    AppendSlEntry(&list->cursors, cursor);
    cursor->serial = cursor->node->serial;
}
}
