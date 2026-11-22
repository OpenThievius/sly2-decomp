/* SPDX-License-Identifier: GPL-3.0-or-later */
/* XFM, a transform object: an LO that keeps its XF pointer at 0x50
   and its local and world matrices at 0x60 and 0xA0. Its parent (LO::psoParent) is an SO whose pxfRoot it takes as its
   own XF and whose axf array it indexes when it clones (func_00231220). Slot 29 of LO (TranslateToPos) sets the position,
   slot 30 the whole matrix and slot 31 (PmatWorld) returns the world matrix: SetXfmParent saves and restores a world
   transform through them. Slots 49 and 50 are XFM's own. Readers: the functions of alo-lo/InitXfm_file.cpp. C++ only. */
#ifndef SLY2_XFM_H
#define SLY2_XFM_H
#include "lo.h"
#include "so.h"
#include "xf.h"
#include "rows3.h"


struct XFM : LO {
    virtual XF *Slot49(int index);                       /* 49: LoadXfmBaseFromBrx passes a 16-bit index, keeps the XF it returns */
    virtual void Slot50(XFM *pxfmSource, XF **ppxf);     /* 50: func_00231220; CloneXfm calls it with the source's and the clone's pxf field */

    /* 0x50 */ XF *pxf;               /* InitXfm (from the parent's pxfRoot), TranslateXfmToPos, SetXfmParent, LoadXfmBaseFromBrx, UpdateXfmMatWorld */
    /* 0x54 */ s32 generation;        /* UpdateXfmMatWorld compares it with the XF's, InvalidateXfmMatWorld sets it to -1 */
    u8 unknown_0x58[0x8];
    /* 0x60 */ union {
        MATRIX4 matLocal;              /* InitXfm (identity), UpdateXfmMatWorld, ApplyXfmProxy, SetXfmParent, func_00231550 */
        ROWS3 rowsLocal;               /* RotateXfmToMat */
    };
    /* 0xA0 */ MATRIX4 matWorld;      /* UpdateXfmMatWorld, GetXfmMatWorld */
};

#if defined(__mips__)
SLY2_OFFSET_CHECK(XFM, pxf, 0x50);
SLY2_OFFSET_CHECK(XFM, matLocal, 0x60);
SLY2_OFFSET_CHECK(XFM, matWorld, 0xA0);
#endif
#endif
