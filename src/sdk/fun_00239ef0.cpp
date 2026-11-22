/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
/* an entry of the alarm list: the next entry, and the address of the pointer that points here (the head or the previous entry's next) */
struct ALARMLISTNODE {
    ALARMLISTNODE *next;
    ALARMLISTNODE **link;
};
extern ALARMLISTNODE *D_002C5A48;
ALARMLISTNODE *func_00239EF0(ALARMLISTNODE *node) {
    ALARMLISTNODE *next = node->next;
    ALARMLISTNODE **link = node->link;
    if (link != 0) {
        *link = next;
    } else {
        D_002C5A48 = next;
    }
    if (next != 0) {
        next->link = node->link;
    }
    node->link = 0;
    return next;
}
}
