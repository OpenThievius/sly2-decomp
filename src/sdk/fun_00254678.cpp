// SPDX-License-Identifier: GPL-3.0-or-later
#include "mpeg.h"
extern "C" int func_00252148(MPEGDEC *, int);
extern "C" void func_00254678(MPEGDEC *decoder)
{
    func_00252148(decoder, 3);
    if (func_00252148(decoder, 1) != 0) {
        func_00252148(decoder, 8);
        func_00252148(decoder, 8);
        decoder->field_0x154 = func_00252148(decoder, 8);
    }
    decoder->field_0x158 = func_00252148(decoder, 0xE);
    func_00252148(decoder, 1);
    decoder->field_0x15C = func_00252148(decoder, 0xE);
}
