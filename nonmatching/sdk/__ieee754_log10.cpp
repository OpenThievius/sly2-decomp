// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"

extern "C" {
s64 __adddf3(s64, s64);
s64 __subdf3(s64, s64);
s64 __muldf3(s64, s64);
s64 __floatsidf(s32);
s64 __ieee754_log(s64);
s64 func_0023DAB0(s64, s32);
extern s64 RO_002AB970;
extern s64 RO_002AB978;
extern s64 RO_002AB980;
extern s64 RO_002AB988;

s64 __ieee754_log10(s64 arg0)
{
    s64 x = arg0;
    s32 hx = (s32)(x >> 32);
    s32 lx = (s32)x;
    s32 k = 0;
    if (!(0xFFFFF < hx)) {
        if (((s64)(hx & 0x7FFFFFFF) | (s64)lx) == 0)
            return RO_002AB970;
        if (hx < 0)
            return func_0023DAB0(__subdf3(x, x), 0);
        k = -0x36;
        x = __muldf3(x, 0x86A0L << 0x2F);
        hx = (s32)(x >> 32);
    }
    if (0x7FEFFFFF < hx)
        return __adddf3(x, x);
    k = k - 0x3FF + (hx >> 20);
    s32 sign = (s32)((u32)k >> 31);
    hx = (hx & 0xFFFFF) | ((0x3FF - sign) << 20);
    s64 dk = __floatsidf(k + sign);
    x = (x & (s64)((u64)(s32)0xFFFF0000 >> 32)) | ((s64)hx << 32);
    s64 logx = __ieee754_log(x);
    s64 scaledK = __muldf3(dk, RO_002AB978);
    s64 sumA = __adddf3(scaledK, __muldf3(logx, RO_002AB980));
    s64 partB = __muldf3(dk, RO_002AB988);
    return __adddf3(sumA, partB);
}
}
