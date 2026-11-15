// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
typedef struct MpegBlock {
    u8 data[0x1C];
} MpegBlock;
typedef struct MpegBuffer {
    u8 pad0[0x4];
    void *coefficients;
    u8 pad8[0x28 - 0x8];
    void (*inverseQuantize[4])(MpegBlock *);
    void (*inverseTransform[4])(MpegBlock *);
    MpegBlock blocks[8];
    void *destination;
    int blockCount;
    int intra;
    int pad134;
    int hasBlocks;
    int noCoefficients;
} MpegBuffer;
typedef struct MpegDecoder {
    u8 pad0[0x5A0];
    MpegBuffer buffers[2];
    u8 pad820[0x830 - 0x820];
    void *scratch;
} MpegDecoder;
extern const char RO_STR_002AC598[];
void func_0024FA38(MpegDecoder *decoder, const char *message);
void func_00252548(void *destination, void *source);
void func_00252458(void *destination, void *scratch, void *source);

void func_00250A38(MpegDecoder *decoder, int index) {
    int blockIndex;
    if (decoder->buffers[index].hasBlocks) {
        for (blockIndex = 0; blockIndex < decoder->buffers[index].blockCount; blockIndex++) {
            decoder->buffers[index].inverseQuantize[blockIndex](&decoder->buffers[index].blocks[blockIndex]);
            decoder->buffers[index].inverseTransform[blockIndex](&decoder->buffers[index].blocks[blockIndex + 4]);
        }
    }
    if (decoder->buffers[index].intra && decoder->buffers[index].noCoefficients) {
        func_0024FA38(decoder, RO_STR_002AC598);
    }
    if (decoder->buffers[index].intra) {
        func_00252548(decoder->buffers[index].destination, decoder->buffers[index].coefficients);
    } else if (decoder->buffers[index].noCoefficients) {
        func_00252548(decoder->buffers[index].destination, decoder->scratch);
    } else {
        func_00252458(decoder->buffers[index].destination, decoder->scratch, decoder->buffers[index].coefficients);
    }
}
