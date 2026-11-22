/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

void bevy_camera_follow_activity(void *pmanager, s32 event, void *pvArgument);
extern char B_002DEB30[];

void func_00140EB0(void *pvArgument) {
    bevy_camera_follow_activity(B_002DEB30, 0x10, pvArgument);
}
