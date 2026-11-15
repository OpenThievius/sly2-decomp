// SPDX-License-Identifier: GPL-3.0-or-later
#include "mpeg.h"
extern "C" {
void func_00252358(MPEGDEC *decoder);
long func_00251FC8(MPEGDEC *decoder);
int func_00252148(MPEGDEC *decoder, int bitCount);

static inline void SendVlcCommand(MPEGDEC *decoder) {
    decoder->commandPending = 0;
    decoder->commandState = 0x30000000;
}

static inline short ReadVlcResult(MPEGDEC *decoder) {
    long result;
    u32 bitPosition;
    long top;
    result = func_00251FC8(decoder);
    bitPosition = *(volatile u32 *)0x10002020;
    top = *(volatile long *)0x10002030;
    decoder->topBits = (int)top;
    if (top < 0) {
        decoder->bitsAvailable = (32 - (bitPosition & 0x1F)) & 0x1F;
    } else {
        decoder->bitsAvailable = 32;
    }
    decoder->field_0x12C = (int)result == 0;
    return (short)(u16)result;
}

static inline short GetMotionCode(MPEGDEC *decoder) {
    func_00252358(decoder);
    *(volatile u32 *)0x10002000 = 0x38000000;
    SendVlcCommand(decoder);
    return ReadVlcResult(decoder);
}

static inline short GetDualPrime(MPEGDEC *decoder) {
    func_00252358(decoder);
    *(volatile u32 *)0x10002000 = 0x3C000000;
    SendVlcCommand(decoder);
    return ReadVlcResult(decoder);
}

static inline void DecodeMotionVector(int *prediction, int rangeSize, int motionCode, int residual, int fullPel) {
    int limit = 16 << rangeSize;
    int vector = fullPel ? (*prediction >> 1) : *prediction;
    if (motionCode > 0) {
        vector += ((motionCode - 1) << rangeSize) + residual + 1;
        if (vector >= limit) {
            vector -= limit + limit;
        }
    } else if (motionCode < 0) {
        vector -= ((-motionCode - 1) << rangeSize) + residual + 1;
        if (vector < -limit) {
            vector += limit + limit;
        }
    }
    *prediction = fullPel ? (vector << 1) : vector;
}

void func_002511C8(MPEGDEC *decoder, int *prediction, int *dualPrime, int horizontalRange, int verticalRange,
                   int dualPrimeFlag, int scaleVertical, int fullPel) {
    int motionCode;
    int residual;

    motionCode = GetMotionCode(decoder);
    residual = (horizontalRange != 0 && motionCode != 0) ? func_00252148(decoder, horizontalRange) : 0;
    DecodeMotionVector(&prediction[0], horizontalRange, motionCode, residual, fullPel);
    if (dualPrimeFlag) {
        dualPrime[0] = GetDualPrime(decoder);
    }

    motionCode = GetMotionCode(decoder);
    residual = (verticalRange != 0 && motionCode != 0) ? func_00252148(decoder, verticalRange) : 0;
    if (scaleVertical) {
        prediction[1] >>= 1;
    }
    DecodeMotionVector(&prediction[1], verticalRange, motionCode, residual, fullPel);
    if (scaleVertical) {
        prediction[1] <<= 1;
    }
    if (dualPrimeFlag) {
        dualPrime[1] = GetDualPrime(decoder);
    }
}
}
