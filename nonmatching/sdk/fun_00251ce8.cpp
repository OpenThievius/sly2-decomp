// SPDX-License-Identifier: GPL-3.0-or-later
#include "mpeg.h"
extern "C" {
extern const char RO_002AC640[];
void func_00252358(MPEGDEC *decoder);
s64 func_00251FC8(MPEGDEC *decoder);
int func_00252230(MPEGDEC *decoder, int bitCount);
void func_00252390(MPEGDEC *decoder, int bitCount);
void func_0024FA90(MPEGDEC *decoder, const char *format, ...);

static inline short ReadVlcResult(MPEGDEC *decoder) {
    s64 result;
    u32 bitPosition;
    s64 top;
    result = func_00251FC8(decoder);
    bitPosition = *(volatile u32 *)0x10002020;
    top = *(volatile s64 *)0x10002030;
    decoder->topBits = (int)top;
    if (top < 0) {
        decoder->bitsAvailable = (32 - (bitPosition & 0x1F)) & 0x1F;
    } else {
        decoder->bitsAvailable = 32;
    }
    decoder->field_0x12C = (int)result == 0;
    return (short)(u16)result;
}

static inline void IssueCommand(MPEGDEC *decoder, u32 command) {
    unsigned state;
    *(volatile u32 *)0x10002000 = command;
    state = command & 0xF0000000;
    decoder->commandState = state;
    if (state == 0x20000000 || state == 0x30000000 || state == 0x40000000) {
        decoder->commandPending = 0;
    } else {
        decoder->commandPending = 1;
    }
}

int func_00251CE8(MPEGDEC *decoder) {
    int increment = 0;
    int again;
    do {
        unsigned int code;
        func_00252358(decoder);
        IssueCommand(decoder, 0x30000000);
        code = (unsigned int)ReadVlcResult(decoder);
        again = 1;
        if (code != 0x22) {
            if (code < 0x23U) {
                if (code != 0) {
                    increment += code;
                    again = 0;
                } else {
                    int skipped = func_00252230(decoder, 0xB);
                    if (decoder->field_0x858 != 0 && skipped == 0xF) {
                        func_00252390(decoder, 0xB);
                    } else {
                        func_0024FA90(decoder, RO_002AC640, code);
                        decoder->field_0x12C = 1;
                        return 1;
                    }
                }
            } else if (code != 0x23) {
                increment += code;
                again = 0;
            } else {
                increment += 0x21;
            }
        }
    } while (again);
    return increment;
}
}
