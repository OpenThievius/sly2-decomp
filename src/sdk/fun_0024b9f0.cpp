// SPDX-License-Identifier: GPL-3.0-or-later
#include "mpeg.h"
extern "C" {
int func_00239450(void);
void func_002394A0(void);

/* The block list a transfer copies: a source address, a block count and a size selector */
struct MPEGSTREAM {
    unsigned int address;     /* 0x00 */
    int unknown_0x4;          /* 0x04 */
    int unknown_0x8;          /* 0x08 */
    int count;                /* 0x0C */
    int sizeSelect;           /* 0x10 */
};

void func_0024B9F0(MPEGDEC *decoder, MPEGSTREAM *stream) {
    int passCount;
    unsigned int baseAddress;
    unsigned int sourceAddress = stream->address & 0x0FFFFFFF;
    baseAddress = decoder->imageBuffer & 0x0FFFFFFF;
    int blockBytes;
    int quadwordCount;
    int destinationStep;
    if (decoder->pictureStructure == 3 || decoder->strideSelect == 0) {
        int selector = decoder->strideSelect;
        blockBytes = stream->sizeSelect * 0x180;
        quadwordCount = blockBytes >> 4;
        if (selector != 0)
            destinationStep = (selector >> 4) * 0x180;
        else
            destinationStep = blockBytes;
        passCount = 1;
    } else {
        destinationStep = (decoder->strideSelect >> 4) * 0xC0;
        blockBytes = (stream->sizeSelect >> 1) * 0x180;
        passCount = 2;
        quadwordCount = blockBytes >> 4;
    }
    int pass;
    for (pass = 0; pass < passCount; pass++) {
        unsigned int destination = baseAddress;
        int index;
        for (index = 0; index < stream->count; index++) {
            int busy = func_00239450();
            *(volatile unsigned int *)0x1000D480 = 0;
            *(volatile unsigned int *)0x1000D410 = sourceAddress;
            *(volatile unsigned int *)0x1000D420 = quadwordCount;
            *(volatile unsigned int *)0x1000D400 = 0x101;
            if (busy != 0)
                func_002394A0();
            while (*(volatile unsigned int *)0x1000D400 & 0x100) {
            }
            busy = func_00239450();
            *(volatile unsigned int *)0x1000D080 = 0;
            *(volatile unsigned int *)0x1000D010 = destination;
            *(volatile unsigned int *)0x1000D020 = quadwordCount;
            *(volatile unsigned int *)0x1000D000 = 0x100;
            if (busy != 0)
                func_002394A0();
            while (*(volatile unsigned int *)0x1000D000 & 0x100) {
            }
            while (*(volatile unsigned int *)0x1000D020 != 0) {
            }
            destination += destinationStep;
            sourceAddress += blockBytes;
        }
        baseAddress += decoder->strideStep * 0xC0;
    }
}
}
