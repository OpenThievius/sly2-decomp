/* SPDX-License-Identifier: GPL-3.0-or-later */
/* PAUSEMENU: the pause menu object (retail's B_003D9ED0). Shared by the module's matched sources
   (src/smartguard-ac). Compiles as C and C++. Names are ours, from what PauseMenu_* and func_001AF390 do.
   Page n of the stack lives at 0x28 + 0x1C * n; a push increments depth, a pop decrements it. */
#ifndef SLY2_PAUSEMENU_H
#define SLY2_PAUSEMENU_H
#include "types.h"

typedef struct PAUSEITEM PAUSEITEM;
typedef struct PAUSELABELS PAUSELABELS;
typedef struct PAUSEPAGE PAUSEPAGE;
typedef struct PAUSEMENUVT PAUSEMENUVT;
typedef struct PAUSEMENU PAUSEMENU;
typedef struct PAUSEBLOT PAUSEBLOT;
typedef struct PAUSEBLOTVT PAUSEBLOTVT;
typedef void (*PFNPAUSEITEM)(PAUSEITEM *);

/* one 0x20-byte menu item: PauseMenu_Update (pfnUpdate, pfnActivate, grf), PauseMenu_Push and func_001AF390 (pfnEnter),
   OpenPauseMenu (kind, grf) */
struct PAUSEITEM {
    s32 kind;
    PFNPAUSEITEM pfnActivate;
    s32 citemSub;          /* func_001B06D8: the sub-page's item count */
    PAUSEITEM *aitemSub;   /* func_001B06D8: the sub-page's items */
    PFNPAUSEITEM pfnUpdate;
    PFNPAUSEITEM pfnEnter;
    PAUSELABELS *plabelsSub; /* 0x18: func_001B0688 passes it to PauseMenu_Push as the sub-page's labels (the push's last argument,
                                PAUSELABELS * in PauseMenu_Push's own signature); one reader on a certain struct */
    u32 grf; /* bit 1: the item closes nothing itself; bit 2: leave the menu open */
};

/* the page's blot (a menu sprite object): only its vtable pointer is read here. Slot at 0x188 is called by PauseMenu_SetState with
   one of a page's selector words, slot at 0x190 by PauseMenu_Update to hide it. Both are called through the delta word before them. */
struct PAUSEBLOTVT {
    u8 unknown_0x0[0x188];
    s16 deltaSelect;
    s16 indexSelect;
    void (*pfnSelect)(void *, s32);
    s16 deltaHide;
    s16 indexHide;
    void (*pfnHide)(void *);
};

struct PAUSEBLOT {
    u8 unknown_0x0[0xC];
    PAUSEBLOTVT *vt;
};

/* a page's label table: words 0 to 2 are selector words PauseMenu_SetState hands to the blot's select slot, words 3 to 7 label ids it plays */
struct PAUSELABELS {
    s32 selEnter;
    s32 selIdle;
    s32 selBack;
    s32 labelEnter;
    s32 labelIdle;
    s32 labelBack;
    s32 labelUp;
    s32 labelDown;
};

struct PAUSEPAGE {
    s32 citem;            /* PauseMenu_Push, PauseMenu_Update */
    PAUSEITEM *aitem;     /* PauseMenu_Push, PauseMenu_Update */
    PAUSEBLOT *pblot;     /* the page's blot */
    s32 fSub;             /* PauseMenu_Update: nonzero pops through func_001AF490 */
    u8 unknown_0x10[0x4];
    s32 iitemCur;         /* PauseMenu_SetState, PauseMenu_Update */
    PAUSELABELS *plabels; /* PauseMenu_Push stores its last argument here */
};

/* the vtable's two entries PauseMenu_SetState calls on leaving and entering state 0 */
struct PAUSEMENUVT {
    u8 unknown_0x0[0x50];
    s16 deltaLeave;
    s16 indexLeave;
    void (*pfnLeave)(void *);
    s16 deltaEnter;
    s16 indexEnter;
    void (*pfnEnter)(void *);
};

struct PAUSEMENU {
    u8 unknown_0x0[0xC];
    PAUSEMENUVT *vt;
    void *pjoy;
    u8 unknown_0x14[0xC];
    PAUSEBLOT *pblot; /* OpenPauseMenu: no menu without it */
    s32 depth;   /* pages on the stack */
    PAUSEPAGE apage[16];
    s32 state;     /* PauseMenu_SetState */
    s32 depthNext; /* -1 when none */
};

#endif
