// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "mpeg.h"
extern const char RO_STR_002AC598[];
void func_0024FA38(MPEGDEC *decoder, const char *message);
void func_00252548(void *destination, void *source);
void func_00252458(void *destination, void *scratch, void *source);

void func_00250A38(MPEGDEC *decoder, int index) {
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
        func_00252548(decoder->buffers[index].destination, decoder->output);
    } else {
        func_00252458(decoder->buffers[index].destination, decoder->output, decoder->buffers[index].coefficients);
    }
}
