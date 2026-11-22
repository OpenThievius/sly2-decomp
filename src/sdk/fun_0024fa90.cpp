/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "mpeg.h"
extern "C" {
s32 func_00236918(char *buffer, s32 size, const char *format, ...);
void func_0024FA38(MPEGDEC *decoder, const char *message);
void func_0024FA90(MPEGDEC *decoder, const char *format, unsigned int value) {
    char message[0x100];
    func_00236918(message, 0x100, format, value);
    func_0024FA38(decoder, message);
}
}
