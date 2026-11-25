/* SPDX-License-Identifier: GPL-3.0-or-later */
/* FRM, the frame being built (g_2dea4c points at it between OpenFrame and CloseFrame). Fields from CloseFrame, OpenFrame, FlushFrames,
   FrameRenderLoop, RenderFrame and ClearPendingFrame (src/frm/). C++ only. */
#ifndef SLY2_FRM_H
#define SLY2_FRM_H
#include "types.h"
#include "dl.h"

struct GIFS;
struct VIFS;

struct FRM {
    /* 0x00 */ s32 cqwGif;     /* CloseFrame: FinalizeFrameGifs counts the quadwords it detached into it */
    /* 0x04 */ QW *pqwGif;     /* RenderFrame: the GIF packet SendDmaSyncGsFinish sends (second call) */
    /* 0x08 */ QW *pqwGifBuffer; /* OpenFrame: the buffer AllocStatic hands the GIF stream (the frame's own words, not the detached packet) */
    /* 0x0C */ s32 cqwGifBuffer; /* OpenFrame: its size in quadwords */
    /* 0x10 */ s32 cqwVif;     /* CloseFrame */
    /* 0x14 */ QW *pqwVif;
    /* 0x18 */ QW *pqwVifBuffer; /* OpenFrame: the same for the VIF stream */
    /* 0x1C */ s32 cqwVifBuffer;
    /* 0x20 */ s32 cqwVifSend; /* CloseFrame: quadwords between pqwVifSend and the end of the VIF packet */
    /* 0x24 */ QW *pqwVifSend; /* CloseFrame, RenderFrame: the VIF packet SendDmaSyncGsFinish sends (first call); OpenFrame clears it */
    u8 unknown_0x28[4];
    /* 0x2C */ u32 grfFontLoaded; /* FEnsureLoaded keeps a bit per font loaded into this frame; OpenFrame clears it */
    /* 0x30 */ u32 grf;        /* OpenFrame sets 1; FlushFrames and FrameRenderLoop test bit 0 (they call BlendPrevFrame) */
    /* 0x34 */ DL dlBlipg;     /* CloseFrame stores B_002DEAF0 here; ClearPendingFrame empties it, running each entry's virtual */
    /* 0x40 */ DL dlBlip;      /* CloseFrame stores B_002DEB00 here; ClearPendingFrame frees its entries to the slot heaps */
    /* 0x4C */ s32 field_0x4C; /* OpenFrame stores g_2ddf54 (a global nobody else names) */
};

/* an element of FRM::dlBlip: ClearPendingFrame frees extra (+0x1088) from one slot heap and the element from another */
struct FRMBLIP {
    u8 unknown_0x0[0x1088];
    /* 0x1088 */ void *extra;
};
#endif
