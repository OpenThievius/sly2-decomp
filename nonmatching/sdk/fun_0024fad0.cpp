// SPDX-License-Identifier: GPL-3.0-or-later
#include "mpeg.h"

struct DualPrimeDecoder {
    char pad[0x184];
    int pictureStructure;
    int topFieldFirst;
};

static inline int Half(int value, int addend) {
    return ((value > 0 ? value + 1 : value) >> 1) + addend;
}

static inline int Third(int value, int addend) {
    int tripled = value * 3;
    return ((value > 0 ? tripled + 1 : tripled) >> 1) + addend;
}

extern "C" void func_0024FAD0(DualPrimeDecoder *decoder, int *out, int *base, int mvx, int mvy) {
    if (decoder->pictureStructure == 3) {
        if (decoder->topFieldFirst) {
            out[0] = Half(mvx, base[0]);
            out[1] = Half(mvy, base[1]) - 1;
            out[2] = Third(mvx, base[0]);
            out[3] = Third(mvy, base[1]) + 1;
        } else {
            out[0] = Third(mvx, base[0]);
            out[1] = Third(mvy, base[1]) - 1;
            out[2] = Half(mvx, base[0]);
            out[3] = Half(mvy, base[1]) + 1;
        }
    } else {
        out[0] = Half(mvx, base[0]);
        out[1] = Half(mvy, base[1]);
        if (decoder->pictureStructure == 1)
            out[1] -= 1;
        else
            out[1] += 1;
    }
}
