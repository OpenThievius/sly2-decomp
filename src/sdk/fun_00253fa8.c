/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "mpeg.h"
void func_0024FA38(MPEGDEC *, const char *);
int func_00252148(MPEGDEC *, int);
void func_00254488(MPEGDEC *);
void func_00253FA8(MPEGDEC *decoder) {
    decoder->loadIntraQuantizerMatrix = func_00252148(decoder, 1);
    if (decoder->loadIntraQuantizerMatrix != 0) {
        func_00254488(decoder);
        *(volatile u32 *)0x10002000 = 0x50000000;
        decoder->commandState = 0x50000000;
        decoder->commandPending = 1;
        func_00254488(decoder);
    }
    decoder->loadNonIntraQuantizerMatrix = func_00252148(decoder, 1);
    if (decoder->loadNonIntraQuantizerMatrix != 0) {
        func_00254488(decoder);
        *(volatile u32 *)0x10002000 = 0x58000000;
        decoder->commandState = 0x50000000;
        decoder->commandPending = 1;
        func_00254488(decoder);
    }
    if (func_00252148(decoder, 1) != 0) {
        func_0024FA38(decoder, "load_chroma_intra_quantizer_matrix == 1");
    }
    if (func_00252148(decoder, 1) != 0) {
        func_0024FA38(decoder, "load_chroma_non_intra_quantizer_matrix == 1");
    }
}
