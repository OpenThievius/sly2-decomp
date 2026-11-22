/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "mpeg.h"
typedef struct Request_2544C8 {
    s32 kind;
    s64 low;
    s64 high;
} Request_2544C8;
int func_0024B670(s32, Request_2544C8 *);
u32 func_00252148(MPEGDEC *, int);
s32 func_00252230(MPEGDEC *, int);
void func_002539D0(MPEGDEC *);
void func_00253C80(MPEGDEC *);
void func_00253D20(MPEGDEC *);
void func_002544C0(MPEGDEC *, int);
void func_00254628(MPEGDEC *);
s32 func_002544C8(MPEGDEC *decoder) {
    Request_2544C8 request;
    u32 startCode;
    for (;;) {
        if (decoder->field_0x878 != 0) {
            return -1;
        }
        func_00254628(decoder);
        while (func_00252230(decoder, 0x18) != 1 && decoder->field_0x878 == 0) {
            func_002544C0(decoder, 8);
        }
        startCode = func_00252148(decoder, 0x20);
        switch (startCode) {
        case 0x1B3: /* sequence header */
            func_002539D0(decoder);
            break;
        case 0x1B8: /* group of pictures header */
            func_00253C80(decoder);
            break;
        case 0x100: /* picture header */
            func_00253D20(decoder);
            request.kind = 5;
            request.low = -1;
            request.high = -1;
            func_0024B670(decoder->field_0x868, &request);
            decoder->timestampLow = request.low;
            decoder->timestampHigh = request.high;
            return decoder->pictureCodingType;
        case 0x1B7: /* sequence end */
            return 0;
        }
    }
}
