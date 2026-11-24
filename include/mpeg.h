/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The SDK's MPEG-2 software decoder (0x24FA38 to 0x254678): MPEGDEC, the decoder object every function of that
   range takes first, and MPEGBUFFER, one of its two 0x140-byte frame buffers (MPEGDEC::buffers, 0x5A0 and 0x6E0).
   Field names and meanings are ours, from what the matched functions do with them. Each source used to declare its
   own view of the object; where two sources named one offset differently the field keeps an offset name
   (`field_0x...`) until a reader settles it. MPEGDEC's class is certain (every function of the range takes it first), so one
   reader is enough for a field when no other source reads the offset as another type (data/matching/include/lo.h's field rule);
   the readers are listed. MPEGWORKAREA is the decoder's bump allocator. C and C++. */
#ifndef SLY2_MPEG_H
#define SLY2_MPEG_H
#include "types.h"

/* One block of a macroblock: a destination, two row counts and the sources of the two halves (0x1C bytes).
   `blocks` of a buffer holds four luma entries, then four chroma entries. */
typedef struct MPEGBLOCK {
    u32 address;
    int offset;
    int firstCount;
    int secondCount;
    int stride;
    u8 *firstSource;
    u8 *secondSource;
} MPEGBLOCK;

typedef struct MPEGBUFFER {
    u8 *base;                                     /* 0x00 */
    void *coefficients;                           /* 0x04 */
    u8 *upper[4];                                 /* 0x08 */
    u8 *lower[4];                                 /* 0x18 */
    void (*inverseQuantize[4])(MPEGBLOCK *);      /* 0x28, one routine per luma block */
    void (*inverseTransform[4])(MPEGBLOCK *);     /* 0x38, one routine per chroma block */
    MPEGBLOCK blocks[8];                          /* 0x48 */
    void *destination;                            /* 0x128 */
    int blockCount;                               /* 0x12C */
    int intra;                                    /* 0x130 */
    int field_0x134;                              /* 0x134 */
    int hasBlocks;                                /* 0x138 */
    int noCoefficients;                           /* 0x13C */
} MPEGBUFFER;

/* The IPU and its two DMA channels as func_00254988 saves them and func_00254A70 restores them (0x24 bytes): channel 4
   (to the IPU, 0x1000B400), channel 3 (from the IPU, 0x1000B000), then IPU_BP (0x10002020) and IPU_CTRL (0x10002010).
   Names from the public PS2 hardware register map; source:hardware. */
typedef struct IPUSTATE {
    s32 toIpuAddress;                             /* 0x00, D4_MADR */
    s32 toIpuTag;                                 /* 0x04, D4_TADR */
    s32 toIpuCount;                               /* 0x08, D4_QWC */
    s32 toIpuControl;                             /* 0x0C, D4_CHCR */
    s32 fromIpuAddress;                           /* 0x10, D3_MADR */
    s32 fromIpuCount;                             /* 0x14, D3_QWC */
    s32 fromIpuControl;                           /* 0x18, D3_CHCR */
    s32 bitPosition;                              /* 0x1C, IPU_BP */
    s32 control;                                  /* 0x20, IPU_CTRL */
} IPUSTATE;

typedef struct MPEGDEC {
    int done;                                     /* 0x000 */
    int field_0x4;                                /* 0x004, func_0024B590 (the reset) clears it */
    int field_0x8;                                /* 0x008, func_0024B590 clears it */
    u8 unknown_0xC[0x68 - 0xC];
    IPUSTATE ipuState;                            /* 0x068, saved and restored around other users of the IPU; func_0024B9A0, func_0024B9C8 */
    u8 unknown_0x8C[0x98 - 0x8C];
    int field_0x98;                               /* 0x098, func_0024B590 sets -1 */
    u8 unknown_0x9C[0xA8 - 0x9C];
    int countA8;                                  /* 0x0A8, the three counts and three indices are read by one function */
    int countAC;                                  /* 0x0AC */
    int countB0;                                  /* 0x0B0 */
    int indexB4;                                  /* 0x0B4 */
    int indexB8;                                  /* 0x0B8 */
    int indexBC;                                  /* 0x0BC */
    int field_0xC0;                               /* 0x0C0, func_0024B590 clears it */
    u8 unknown_0xC4[0xE8 - 0xC4];
    int targetE8;                                 /* 0x0E8 */
    unsigned int imageBuffer;                     /* 0x0EC */
    u8 unknown_0xF0[4];
    int strideSelect;                             /* 0x0F4, a multiple of 16: 0 means the destination steps by the block size; source:func_0024B9F0 */
    int strideStep;                               /* 0x0F8, the base advances by strideStep * 0xC0 per pass; source:func_0024B9F0 */
    int field_0xFC;                               /* 0x0FC, func_00253C80 (picture start) clears it; reader: func_00253C80 */
    u8 unknown_0x100[0x128 - 0x100];
    int field_0x128;                              /* 0x128, func_0024B590 clears it */
    int field_0x12C;                              /* a fault flag in one reader, "last code zero" in another */
    u8 unknown_0x130[0x134 - 0x130];
    int field_0x134;                              /* 0x134, low 12 bits plus (extension bits << 12); reader: func_00253E68 (sequence extension) */
    int field_0x138;                              /* 0x138, the same for the other dimension; reader: func_00253E68 */
    int width;                                    /* 0x13C, in macroblocks */
    int height;                                   /* 0x140 */
    int field_0x144;                              /* 0x144, adds 12 extension bits << 18; reader: func_00253E68 */
    int field_0x148;                              /* 0x148, adds 8 extension bits << 10; reader: func_00253E68 */
    int field_0x14C;                              /* 0x14C, one bit of the sequence extension; readers: func_00253E68, func_002547A0 */
    int field_0x150;                              /* 0x150, two bits of the sequence extension, 1 expected; reader: func_00253E68 */
    int field_0x154;                              /* 0x154, an 8-bit value from the sequence header */
    int field_0x158;                              /* 0x158, 14 bits */
    int field_0x15C;                              /* 0x15C, 14 bits */
    int pictureCodingType;                        /* 0x160 */
    int fullPelForward;                           /* 0x164 */
    int forwardCode;                              /* 0x168 */
    int fullPelBackward;                          /* 0x16C */
    int backwardCode;                             /* 0x170 */
    int motionCode[2][2];                         /* 0x174, [direction][horizontal, vertical] */
    int pictureStructure;                         /* 0x184, 3 is a frame picture */
    int topFieldFirst;                            /* 0x188, picks which dual-prime vector pair goes first; source:func_0024FAD0 */
    int framePredFrameDct;                        /* 0x18C */
    int concealmentVectors;                       /* 0x190 */
    u8 unknown_0x194[0x1B4 - 0x194];
    int field_0x1B4;                              /* 0x1B4, func_00253C80 reads one bit-count-1 value into it; reader: func_00253C80 */
    int field_0x1B8;                              /* 0x1B8, the same; reader: func_00253C80 */
    int pictureIndex;                             /* 0x1BC, gopBase + temporal reference; func_00253D20 */
    int resetDcPredictor;                         /* 0x1C0 */
    int quantizerScaleCode;                       /* 0x1C4 */
    u8 unknown_0x1C8[0x5A0 - 0x1C8];
    MPEGBUFFER buffers[2];                        /* 0x5A0 */
    int bufferIndex;                              /* 0x820 */
    int field_0x824;                              /* 0x824, cleared with the buffer index by one reader */
    int commandPending;                           /* 0x828 */
    unsigned int commandState;                    /* 0x82C */
    void *output;                                 /* 0x830, the destination or scratch picture */
    int stop;                                     /* 0x834 */
    s64 timestampLow;                             /* 0x838, reply to a kind 5 request of func_0024B670; func_002544C8 */
    s64 timestampHigh;                            /* 0x840 */
    int topBits;                                  /* 0x848 */
    int bitsAvailable;                            /* 0x84C */
    int loadIntraQuantizerMatrix;                 /* 0x850, func_00253FA8 */
    int loadNonIntraQuantizerMatrix;              /* 0x854 */
    int field_0x858;                              /* "mpeg2" in one reader, "keep going" in another */
    int gopBase;                                  /* 0x85C, picture index of the first picture of the group; func_00253C80, func_00253D20 */
    int maxPictureIndex;                          /* 0x860, highest pictureIndex so far */
    int newGop;                                   /* 0x864, set by a group header, cleared by the first picture after it */
    int field_0x868;                              /* 0x868 */
    u8 unknown_0x86C[0x878 - 0x86C];
    int field_0x878;                              /* "aborted" in one reader */
    int sameFrame;                                /* 0x87C */
} MPEGDEC;

/* What the decoder's entry points are given: the decoder sits at 0x40 (func_0024ACD8, sceMpegIsEnd, func_0024B590, func_0024B7A8,
   func_0024B9A0, func_0024B9C8) */
typedef struct MPEGHANDLE {
    u8 unknown_0x0[0x8];
    int field_0x8;                                /* 0x08, func_0024B590 (the reset) clears it */
    u8 unknown_0xC[0x40 - 0xC];
    MPEGDEC *state;                               /* 0x40 */
} MPEGHANDLE;

/* The decoder's bump allocator: the area [base, base + size), the next free offset `used` and a mark `start` that func_0024B910
   sets to `used` and func_0024B920 returns `used` to. func_0024B930 hands out aligned blocks from it. */
typedef struct MPEGWORKAREA {
    u32 base;
    u32 size;
    u32 used;
    u32 start;
} MPEGWORKAREA;

typedef char check_MPEGBLOCK_size[(sizeof(MPEGBLOCK) == 0x1C) ? 1 : -1];
typedef char check_MPEGBUFFER_size[(sizeof(MPEGBUFFER) == 0x140) ? 1 : -1];
typedef char check_MPEGBUFFER_blocks[((uptr)&((MPEGBUFFER *)0)->blocks == 0x48) ? 1 : -1];
typedef char check_MPEGBUFFER_destination[((uptr)&((MPEGBUFFER *)0)->destination == 0x128) ? 1 : -1];
typedef char check_MPEGBUFFER_noCoefficients[((uptr)&((MPEGBUFFER *)0)->noCoefficients == 0x13C) ? 1 : -1];
typedef char check_MPEGDEC_buffers[((uptr)&((MPEGDEC *)0)->buffers == 0x5A0) ? 1 : -1];
typedef char check_MPEGDEC_bufferIndex[((uptr)&((MPEGDEC *)0)->bufferIndex == 0x820) ? 1 : -1];
typedef char check_MPEGDEC_output[((uptr)&((MPEGDEC *)0)->output == 0x830) ? 1 : -1];
typedef char check_MPEGDEC_topBits[((uptr)&((MPEGDEC *)0)->topBits == 0x848) ? 1 : -1];
typedef char check_MPEGDEC_stop[((uptr)&((MPEGDEC *)0)->stop == 0x834) ? 1 : -1];
typedef char check_MPEGDEC_imageBuffer[((uptr)&((MPEGDEC *)0)->imageBuffer == 0xEC) ? 1 : -1];
typedef char check_MPEGDEC_strideSelect[((uptr)&((MPEGDEC *)0)->strideSelect == 0xF4) ? 1 : -1];
typedef char check_MPEGDEC_strideStep[((uptr)&((MPEGDEC *)0)->strideStep == 0xF8) ? 1 : -1];
typedef char check_MPEGDEC_pictureStructure[((uptr)&((MPEGDEC *)0)->pictureStructure == 0x184) ? 1 : -1];
typedef char check_MPEGDEC_quantizerScaleCode[((uptr)&((MPEGDEC *)0)->quantizerScaleCode == 0x1C4) ? 1 : -1];
typedef char check_MPEGDEC_sameFrame[((uptr)&((MPEGDEC *)0)->sameFrame == 0x87C) ? 1 : -1];
typedef char check_MPEGDEC_ipuState[((uptr)&((MPEGDEC *)0)->ipuState == 0x68) ? 1 : -1];
typedef char check_MPEGDEC_field_0x128[((uptr)&((MPEGDEC *)0)->field_0x128 == 0x128) ? 1 : -1];
typedef char check_MPEGDEC_pictureIndex[((uptr)&((MPEGDEC *)0)->pictureIndex == 0x1BC) ? 1 : -1];
typedef char check_MPEGDEC_timestampLow[((uptr)&((MPEGDEC *)0)->timestampLow == 0x838) ? 1 : -1];
typedef char check_MPEGDEC_newGop[((uptr)&((MPEGDEC *)0)->newGop == 0x864) ? 1 : -1];
typedef char check_MPEGHANDLE_state[((uptr)&((MPEGHANDLE *)0)->state == 0x40) ? 1 : -1];
typedef char check_MPEGDEC_field_0x878[((uptr)&((MPEGDEC *)0)->field_0x878 == 0x878) ? 1 : -1];

#endif
