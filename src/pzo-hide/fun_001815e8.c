/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

/* a MOUNT seen from C (mount.h is C++ only): only the field Grab_SetState sets */
struct MOUNTVIEW {
    u8 unknown_0x0[0x294];
    void *pobjB;
};

void Mount_SetState(struct MOUNT *, s32);
void bevy_camera_follow_activity(void *, s32, struct GRAB *);
void func_0017F4C0(struct GRAB *, struct ANIMENTRY *);
void func_00181728(struct GRAB *);
extern char B_002DEB30;

void func_001815E8(struct GRAB *grab, s32 state) {
    struct ANIMENTRY *pentry;

    if (grab->state != state) {
        if ((grab->state == 1) && (grab->pmount != 0)) {
            func_00181728(grab);
        }
        grab->state = state;
        grab->tState = g_2dded0.t;
        switch (state) {
        case 1:
            ((struct MOUNTVIEW *)grab->pmount)->pobjB = grab->anchor;
            Mount_SetState(grab->pmount, 3);
            break;
        case 2:
            bevy_camera_follow_activity(&B_002DEB30, 0x39, grab);
            break;
        }
        if (state != -1) {
            pentry = &grab->aentry[state];
        } else {
            pentry = 0;
        }
        func_0017F4C0(grab, pentry);
    }
}
