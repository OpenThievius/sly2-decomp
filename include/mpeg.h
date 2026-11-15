/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The SDK's MPEG-2 software decoder (0x24FA38 to 0x254678): MPEGDEC, the decoder object every function of that
   range takes first, and MPEGBUFFER, one of its two 0x140-byte frame buffers (MPEGDEC::buffers, 0x5A0 and 0x6E0).
   Field names and meanings are ours, from what the matched functions do with them. Each source used to declare its
   own view of the object; where two sources named one offset differently the field keeps an offset name
   (`field_0x...`) until a reader settles it. A field enters this header when a second source agrees on its offset and
   size, or when it only adds detail inside a region two sources agree on (MPEGBLOCK in `blocks`). C and C++. */
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

typedef struct MPEGDEC {
    int done;                                     /* 0x000 */
    u8 pad4[0xA8 - 0x4];
    int countA8;                                  /* 0x0A8, the three counts and three indices are read by one function */
    int countAC;                                  /* 0x0AC */
    int countB0;                                  /* 0x0B0 */
    int indexB4;                                  /* 0x0B4 */
    int indexB8;                                  /* 0x0B8 */
    int indexBC;                                  /* 0x0BC */
    u8 padC0[0xE8 - 0xC0];
    int targetE8;                                 /* 0x0E8 */
    unsigned int imageBuffer;                     /* 0x0EC */
    u8 padF0[0x12C - 0xF0];
    int field_0x12C;                              /* a fault flag in one reader, "last code zero" in another */
    u8 pad130[0x184 - 0x130];
    int mode;                                     /* 0x184 */
    u8 pad188[0x5A0 - 0x188];
    MPEGBUFFER buffers[2];                        /* 0x5A0 */
    int bufferIndex;                              /* 0x820 */
    u8 pad824[0x828 - 0x824];
    int commandPending;                           /* 0x828 */
    unsigned int commandState;                    /* 0x82C */
    void *output;                                 /* 0x830, the destination or scratch picture */
    int stop;                                     /* 0x834 */
    u8 pad838[0x848 - 0x838];
    int topBits;                                  /* 0x848 */
    int bitsAvailable;                            /* 0x84C */
    u8 pad850[0x858 - 0x850];
    int field_0x858;                              /* "mpeg2" in one reader, "keep going" in another */
    u8 pad85C[0x868 - 0x85C];
    int field_0x868;                              /* 0x868 */
    u8 pad86C[0x878 - 0x86C];
    int field_0x878;                              /* "aborted" in one reader */
} MPEGDEC;

/* What the decoder's entry points are given: the decoder sits at 0x40 (one reader so far: func_0024ACD8) */
typedef struct MPEGHANDLE {
    u8 pad0[0x40];
    MPEGDEC *state;                               /* 0x40 */
} MPEGHANDLE;

typedef char check_MPEGBLOCK_size[(sizeof(MPEGBLOCK) == 0x1C) ? 1 : -1];
typedef char check_MPEGBUFFER_size[(sizeof(MPEGBUFFER) == 0x140) ? 1 : -1];
typedef char check_MPEGBUFFER_blocks[((unsigned int)&((MPEGBUFFER *)0)->blocks == 0x48) ? 1 : -1];
typedef char check_MPEGBUFFER_destination[((unsigned int)&((MPEGBUFFER *)0)->destination == 0x128) ? 1 : -1];
typedef char check_MPEGBUFFER_noCoefficients[((unsigned int)&((MPEGBUFFER *)0)->noCoefficients == 0x13C) ? 1 : -1];
typedef char check_MPEGDEC_buffers[((unsigned int)&((MPEGDEC *)0)->buffers == 0x5A0) ? 1 : -1];
typedef char check_MPEGDEC_bufferIndex[((unsigned int)&((MPEGDEC *)0)->bufferIndex == 0x820) ? 1 : -1];
typedef char check_MPEGDEC_output[((unsigned int)&((MPEGDEC *)0)->output == 0x830) ? 1 : -1];
typedef char check_MPEGDEC_topBits[((unsigned int)&((MPEGDEC *)0)->topBits == 0x848) ? 1 : -1];
typedef char check_MPEGDEC_stop[((unsigned int)&((MPEGDEC *)0)->stop == 0x834) ? 1 : -1];
typedef char check_MPEGDEC_imageBuffer[((unsigned int)&((MPEGDEC *)0)->imageBuffer == 0xEC) ? 1 : -1];
typedef char check_MPEGDEC_field_0x878[((unsigned int)&((MPEGDEC *)0)->field_0x878 == 0x878) ? 1 : -1];

#endif
