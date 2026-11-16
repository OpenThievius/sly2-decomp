// SPDX-License-Identifier: GPL-3.0-or-later
// Double bits to a rounded integer clamped to 9999; the low word is sign-extended through a 32.32 shift pair.
long func_002358A0(unsigned long bits)
{
    unsigned long mantissa;
    long exponent;
    long fixed;
    mantissa = bits;
    exponent = (mantissa << 1) >> 53;
    exponent -= 0x433;
    if (exponent < -0x35) {
        return 0;
    }
    if (exponent >= 0xD) {
        return 0x270F;
    }
    mantissa = (mantissa << 12) >> 12;
    mantissa |= 0x10000000000000UL;
    if (exponent < 0) {
        exponent = -exponent;
        mantissa >>= (int)(exponent - 2);
        if ((mantissa & 3) == 3) {
            mantissa = (mantissa >> 2) + 1;
        } else {
            mantissa >>= 2;
        }
        fixed = mantissa << 32;
    } else {
        mantissa <<= (int)exponent;
        fixed = mantissa << 32;
    }
    return fixed >> 32;
}
