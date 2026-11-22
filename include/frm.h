/* SPDX-License-Identifier: GPL-3.0-or-later */
/* FRM, the frame being built (g_2dea4c points at it between OpenFrame and CloseFrame). Fields from CloseFrame, RenderFrame and
   ClearPendingFrame (src/frm/). C++ only. */
#ifndef SLY2_FRM_H
#define SLY2_FRM_H
#include "types.h"
#include "dl.h"

struct GIFS;
struct VIFS;

struct FRM {
    /* 0x00 */ s32 cqwGif;     /* CloseFrame: FinalizeFrameGifs counts the quadwords it detached into it */
    /* 0x04 */ QW *pqwGif;     /* RenderFrame: the GIF packet SendDmaSyncGsFinish sends (second call) */
    u8 unknown_0x8[8];
    /* 0x10 */ s32 cqwVif;     /* CloseFrame */
    /* 0x14 */ QW *pqwVif;
    u8 unknown_0x18[8];
    /* 0x20 */ s32 cqwVifSend; /* CloseFrame: quadwords between pqwVifSend and the end of the VIF packet */
    /* 0x24 */ QW *pqwVifSend; /* CloseFrame, RenderFrame: the VIF packet SendDmaSyncGsFinish sends (first call) */
    u8 unknown_0x28[0xC];        /* FEnsureLoaded keeps a bit per font loaded into this frame at 0x2C (one reader, not a method: not declared) */
    /* 0x34 */ DL dlBlipg;     /* CloseFrame stores B_002DEAF0 here; ClearPendingFrame empties it, running each entry's virtual */
    /* 0x40 */ DL dlBlip;      /* CloseFrame stores B_002DEB00 here; ClearPendingFrame frees its entries to the slot heaps */
};

/* an element of FRM::dlBlip: ClearPendingFrame frees extra (+0x1088) from one slot heap and the element from another */
struct FRMBLIP {
    u8 unknown_0x0[0x1088];
    /* 0x1088 */ void *extra;
};
#endif
