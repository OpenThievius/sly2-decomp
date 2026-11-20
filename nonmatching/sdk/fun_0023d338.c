/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

typedef struct Unpacked {
    u32 kind;
    s32 sign;
    s32 exponent;
    s32 pad;
    union {
        u64 ll;
        u32 l[2];
    } fraction;
} Unpacked;

typedef union PackedDouble {
    u64 whole;
    struct {
        u64 fraction : 52;
        u64 exponent : 11;
        u64 sign : 1;
    } bits;
} PackedDouble;

u64 func_0023D338(Unpacked* in)
{
    PackedDouble out;
    u64 fraction = in->fraction.ll;
    s32 sign = in->sign;
    s32 exponent = 0;

    if (in->kind < 2) {
        exponent = 0x7FF;
        fraction |= 0x8000ull << 36;
    } else if ((in->kind ^ 4) == 0) {
        exponent = 0x7FF;
        fraction = 0;
    } else if ((in->kind ^ 2) == 0) {
        fraction = 0;
    } else if (fraction != 0) {
        exponent = in->exponent;
        if (exponent < -0x3FE) {
            s32 shift = -0x3FE - exponent;
            if (shift <= 0x38)
                fraction >>= shift;
            else
                fraction = 0;
            exponent = 0;
        } else if (exponent > 0x3FF) {
            exponent = 0x7FF;
            fraction = 0;
        } else {
            exponent += 0x3FF;
            if ((fraction & 0xFF) == 0x80) {
                if (fraction & 0x100)
                    fraction += 0x80;
            } else {
                fraction += 0x7F;
            }
            if (fraction > (~0ull >> 3)) {
                fraction >>= 1;
                exponent++;
            }
        }
        fraction >>= 8;
    }
    out.bits.fraction = fraction;
    out.bits.exponent = exponent;
    out.bits.sign = sign;
    return out.whole;
}
