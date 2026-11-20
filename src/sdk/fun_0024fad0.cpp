// SPDX-License-Identifier: GPL-3.0-or-later
#include "mpeg.h"

struct DualPrimeDecoder {
    char pad[0x184];
    int pictureStructure;
    int topFieldFirst;
};

// Dual-prime motion vectors (ISO/IEC 13818-2 7.6.3.6): the vector scaled by 1/2
// or 3/2, rounded away from zero, plus the differential vector and the vertical
// field-parity shift.
static inline int Half(int value, int differential, int shift) {
    return ((value > 0 ? value + 1 : value) >> 1) + differential + shift;
}

static inline int ThreeHalves(int value, int differential, int shift) {
    int tripled = value * 3;
    return ((value > 0 ? tripled + 1 : tripled) >> 1) + differential + shift;
}

extern "C" void func_0024FAD0(DualPrimeDecoder *decoder, int *out, int *base, int mvx, int mvy) {
    if (decoder->pictureStructure == 3) {
        if (decoder->topFieldFirst) {
            out[0] = Half(mvx, base[0], 0);
            out[1] = Half(mvy, base[1], -1);
            out[2] = ThreeHalves(mvx, base[0], 0);
            out[3] = ThreeHalves(mvy, base[1], 1);
        } else {
            out[0] = ThreeHalves(mvx, base[0], 0);
            out[1] = ThreeHalves(mvy, base[1], -1);
            out[2] = Half(mvx, base[0], 0);
            out[3] = Half(mvy, base[1], 1);
        }
    } else {
        out[0] = Half(mvx, base[0], 0);
        out[1] = Half(mvy, base[1], 0);
        if (decoder->pictureStructure == 1)
            out[1] -= 1;
        else
            out[1] += 1;
    }
}
