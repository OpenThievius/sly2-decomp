/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SHD and TEX, the world's shaders (0x1EB1A8-0x1EC940): LoadShdFromBrx fills each 0x2C-byte SHD of the array at B_003DCFEC (count
   B_003DCFE8) and its textures, FillShaders builds each one's DMA parts, PshdFindShader looks one up by object id. Fields are named
   from the loader and the readers listed. No types.h: FillShaders declares its own opaque QW, which types.h's typedef would clash
   with (the reason rgba.h has none either). C++ only. */
#ifndef SLY2_SHD_H
#define SLY2_SHD_H
#include "rgba.h"

struct SHD;

/* One texture of a shader (0x14 bytes); LoadTexFromBrx reads its first eight bytes from the stream. */
struct TEX {
    unsigned char unknown_0x0[4];
    /* 0x4 */ unsigned short flags;    /* reader: func_001EA750 (bit 0: clamp S, bit 1: clamp T; one reader, the class is certain: FillShaders passes atex to it) */
    /* 0x6 */ unsigned char cbmp;      /* LoadTexFromBrx: how many bitmaps; LoadShdFromBrx copies the first texture's into SHD::cframe; func_001EB678 sizes the frame table by it */
    /* 0x7 */ unsigned char cpal;      /* LoadTexFromBrx: how many palettes */
    /* 0x8 */ struct SHD *owner;       /* LoadShdFromBrx sets it to the shader (the stream does not hold it) */
    /* 0xC */ unsigned *abmp;          /* LoadTexFromBrx: the bitmap table's entries (B_003DCFF4 + index * 0x28) */
    /* 0x10 */ unsigned *apal;         /* LoadTexFromBrx: the palette table's entries (B_003DCFFC + index * 0x20), 0 for index 0xFFFF */
};

/* A shader's part: a count and its memory (LoadShdFromBrx allocates it; FillShaders reads the same pair as a DMA reference,
   quadword count and quadwords). */
struct SHDPART {
    int count;
    void *memory;
};

struct SHD {
    /* 0x00 */ int oid;                /* PshdFindShader, func_001EB678 (copies it to the frame table) */
    /* 0x04 */ unsigned char kind;     /* LoadShdFromBrx and FillShaders switch on it (0 to 7) */
    /* 0x05 */ unsigned char grf;      /* LoadShdFromBrx (0x20, 2), LoadShadersFromBrx (0x40), FillShaders, func_001EB678 */
    /* 0x06 */ unsigned char field_0x6; /* func_001EB678 copies it to the frame table */
    unsigned char unknown_0x7[1];
    /* 0x08 */ RGBA rgba8;             /* LoadShdFromBrx filters its address (FilterColorRgba8); func_001EB678 copies it */
    /* 0x0C */ RGBA rgbaC;             /* LoadShdFromBrx filters its address; FillShaders halves its bytes */
    /* 0x10 */ RGBA rgbaTex;           /* LoadShdFromBrx filters its address; FillShaders reads it as the texture colour */
    unsigned char unknown_0x14[3];
    /* 0x17 */ unsigned char ctex;     /* LoadShdFromBrx: how many textures to allocate and load */
    /* 0x18 */ struct TEX *atex;       /* LoadShdFromBrx; func_001EB678; FillShaders passes it to func_001EA750 */
    /* 0x1C */ int cpart;              /* LoadShdFromBrx: how many parts its kind has */
    /* 0x20 */ struct SHDPART *apart;  /* LoadShdFromBrx allocates and fills them; FillShaders walks them as DMA references */
    /* 0x24 */ int cframe;             /* LoadShdFromBrx: the first texture's cbmp */
    /* 0x28 */ int field_0x28;         /* LoadShdFromBrx: the entry of B_003DD004 the stream names */
};

#if defined(__mips__)
typedef char check_SHD_size[(sizeof(struct SHD) == 0x2C) ? 1 : -1];
typedef char check_TEX_size[(sizeof(struct TEX) == 0x14) ? 1 : -1];
#endif
#endif
