// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
/* the camera follow manager at 0x2DEB30 as bevy_camera_follow_activity reads it: the argument of the event this function raises is at 0xC */
struct GAME { u8 unknown_0x0[0xC]; s32 arg; };
extern "C" {
CRef func_001D8B20(const CRef &value, const char *first, ...);
int sprintf(char *, const char *, ...);
void bevy_camera_follow_activity(GAME *, int, int);
extern const char RO_002A79A0[];
extern const char RO_002A79A8[];
extern const char RO_002A79B8[];
extern GAME B_002DEB30;
}

void SetGadgetAcquired(int gadget, int acquired)
{
    CRef ref;
    char name[0x20];
    ref.m_tagk = TAGK_Nil;
    sprintf(name, RO_002A79A0, gadget);
    ref = func_001D8B20(CRef(acquired != 0, TAGK_Bool), RO_002A79A8, RO_002A79B8, name, 0);
    if (acquired != 0) {
        B_002DEB30.arg = gadget;
        bevy_camera_follow_activity(&B_002DEB30, 0x3B, 0);
    }
}
