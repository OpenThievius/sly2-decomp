/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sl.h"
/* a container its cursors watch (named after Vector_Init; not the 3D VECTOR of sly2.h) */
struct VECTORCONTAINER {
    s32 serial;
    SL cursors; /* 0x04, every cursor opened on the vector */
};
struct VECTORCURSOR {
    VECTORCONTAINER *container;
    u8 unknown_0x4[0x20];
    s32 serial; /* 0x24, the container's serial when the cursor was opened */
};
extern "C" {
void AppendSlEntry(SL *list, void *entry);

void Vector_Init(VECTORCURSOR *cursor, VECTORCONTAINER *container) {
    cursor->container = container;
    AppendSlEntry(&container->cursors, cursor);
    cursor->serial = container->serial;
}
}
