/* SPDX-License-Identifier: GPL-3.0-or-later */
/* source:sly1-decomp soft_float.c PackDouble (src/lib, AGPL-3.0, same maintainers), a draft */
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

#define IS_NAN(p) ((p)->kind < 2)
#define IS_ZERO(p) (((p)->kind ^ 2) == 0)
#define IS_INF(p) (((p)->kind ^ 4) == 0)

u64 func_0023D338(Unpacked* p)
{
    union {
        u64 u;
        struct {
            u64 mant : 52;
            u64 expo : 11;
            u64 sign : 1;
        } b;
    } bits;
    u64 mant = p->fraction.ll;
    s32 expo = 0;
    u32 sign = p->sign;

    if (IS_NAN(p)) {
        expo = 0x7FF;
        mant = mant | ((u64)1 << 51);
    } else if (IS_INF(p)) {
        expo = 0x7FF;
        mant = 0;
    } else if (IS_ZERO(p)) {
        mant = 0;
    } else if (mant != 0) {
        s32 e = p->exponent;
        if (e < -0x3FE) {
            s32 sh = -0x3FE - e;
            if (sh > 0x38) {
                mant = 0;
            } else {
                mant = mant >> sh;
            }
            mant = mant >> 8;
        } else if (e >= 0x400) {
            expo = 0x7FF;
            mant = 0;
        } else {
            expo = e + 0x3FF;
            if ((mant & 0xFF) == 0x80) {
                if ((mant & 0x100) != 0) {
                    mant = mant + 0x80;
                }
            } else {
                mant = mant + 0x7F;
            }
            if (mant > 0x1FFFFFFFFFFFFFFFull) {
                mant = mant >> 1;
                expo = expo + 1;
            }
            mant = mant >> 8;
        }
    }

    bits.b.mant = mant;
    bits.b.expo = expo;
    bits.b.sign = sign;
    return bits.u;
}
