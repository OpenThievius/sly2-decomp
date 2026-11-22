/* SPDX-License-Identifier: GPL-3.0-or-later */
/* EPSEL, the episode-select screen object: SetEpselMode, SetEpselHint and LabelFromEpselMode (src/emitter-font/) read it. Its
   vtable pointer is at +0xC and slot 49 is the blot's select slot, as pausemenu.h's PAUSEBLOTVT declares it (called through the
   delta word before it). C and C++. */
#ifndef SLY2_EPSEL_H
#define SLY2_EPSEL_H
#include "types.h"
#include "pausemenu.h"

struct EPSEL {
    u8 unknown_0x0[0xC];
    /* 0x0C */ PAUSEBLOTVT *vt;
    u8 unknown_0x10[0x60];
    /* 0x70 */ s32 field_0x70;     /* SetEpselMode sets the three to -1 on every mode change */
    /* 0x74 */ s32 field_0x74;
    /* 0x78 */ s32 field_0x78;
    u8 unknown_0x7C[0x94];
    /* 0x110 */ s32 episode;       /* SetEpselMode, LabelFromEpselMode (row of D_002BE080) */
    /* 0x114 */ s32 episodeNext;   /* SetEpselMode: moved into episode on leaving mode 4 or 6 */
    u8 unknown_0x118[4];
    /* 0x11C */ s32 mode;          /* SetEpselMode, LabelFromEpselMode */
    /* 0x120 */ s32 sub;           /* SetEpselMode, LabelFromEpselMode (mode 8's column of D_002BE1B8) */
    /* 0x124 */ f32 tMode;         /* SetEpselMode: g_2ddf0c when the mode changed */
    /* 0x128 */ s32 field_0x128;   /* LabelFromEpselMode: row of D_002BE1B8 */
    /* 0x12C */ s32 hint;          /* SetEpselHint */
    /* 0x130 */ f32 tHint;         /* SetEpselHint: g_2ddf0c when the hint changed */
};
#endif
