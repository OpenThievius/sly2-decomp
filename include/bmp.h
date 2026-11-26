/* SPDX-License-Identifier: GPL-3.0-or-later */
/* BMP, a bitmap record of the font loader (src/font/LoadBmpFromBrx.cpp reads its first 0x18 bytes from the stream, func_0015F710 hands it
   to BuildBmpTex0 and BuildBmpGifs) and CLUT, the palette beside it. Only the fields these two functions read are named; the others
   (size, format: src/gs/BuildBmp*) are gaps here. C++ only. */
#ifndef FONT_BMP_H
#define FONT_BMP_H
#include "types.h"

struct BMP {
    /* 0x00 */ s32 oid;          /* LoadBmpFromBrx: the key of PidFindInIdTableA_1ed4e0 */
    /* 0x04 */ u8 bmpk;          /* 1: pixels are not stored in the stream; 0: not loaded */
    /* 0x05 */ s8 ccond;         /* LoadBmpFromBrx: the number of condition ids that follow */
    u8 unknown_0x6[6];
    /* 0x0C */ u8 field_0xC;     /* FBuildUploadBitmapGifs: while it is 0 the ZPR cursor is padded to 0x20 before the allocation (one reader) */
    u8 unknown_0xD[1];
    /* 0x0E */ u16 iblock;       /* func_0015F710: the size in GS blocks it asks AllocZpr for */
    /* 0x10 */ s32 cbPixels;     /* bytes of pixels */
    /* 0x14 */ void *pvPixels;   /* LoadBmpFromBrx allocates it; func_0015F710 copies it into the font (pqwBmp2) */
    /* 0x18 */ s32 cqw;          /* quadwords of pixels, rounded up; func_0015F710 copies it into the font (cbBmp2) */
    u8 unknown_0x1C[4];
    /* 0x20 */ s64 tex0;         /* BuildBmpTex0 builds it, func_0015F710 copies it into the font */
};

struct CLUT {
    /* 0x00 */ s32 oid;          /* FBuildUploadBitmapGifs: the key of PidFindInIdTableB (AddToIdTableB adds the record; the BMP's oid is the same word) */
    /* 0x04 */ u8 group;         /* FBuildUploadBitmapGifs, PqwVifsBitmapUpload: the upload group it is built with (BMP::bmpk's place) */
    u8 unknown_0x5[5];
    /* 0x0A */ u16 iblock;
    /* 0x0C */ void *pqw2;
    /* 0x10 */ s32 cb2;
    u8 unknown_0x14[4];
    /* 0x18 */ s64 tex2;
};
#endif
