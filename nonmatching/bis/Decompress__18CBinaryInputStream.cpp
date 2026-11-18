// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"

struct CBinaryInputStream {
    unsigned flags;
    unsigned char *pbCur;
    int cbCur;
    int cbPumped;
    unsigned char *pbRaw;
    int cbRaw;
    int grfBits;
    int cbCarry;
    int unknown20;
    unsigned char *pbWindow;
    char pad[0x8];
    virtual void RawPump();
    void Decompress();
};

void CBinaryInputStream::Decompress()
{
    unsigned char *window = pbWindow;
    int cbSrc = cbRaw;
    unsigned char *pbSrc = pbRaw;
    int bits = grfBits;
    int cbOut = 0;
    int full;
    if (cbCarry > 0) {
        memcpy(window, window + 0x2000, cbCarry);
        cbOut = cbCarry;
    }
    while ((full = cbOut < 0x2000) != 0) {
        unsigned char flagByte;
        int base = 0xFF00;
        unsigned char first;
        bits >>= 1;
        cbSrc--;
        if ((bits & 0x100) == 0) {
            if (cbSrc < 0) {
                RawPump();
                if (cbRaw < 1)
                    break;
                pbSrc = pbRaw;
                cbSrc = cbRaw - 1;
            }
            flagByte = *pbSrc;
            pbSrc++;
            bits = flagByte + base;
            cbSrc--;
        }
        if (cbSrc < 0) {
            RawPump();
            if (cbRaw < 1)
                break;
            pbSrc = pbRaw;
            cbSrc = cbRaw - 1;
        }
        first = *pbSrc;
        pbSrc++;
        if (bits & 1) {
            window[cbOut] = first;
            cbOut++;
        } else {
            unsigned char second;
            int match;
            int run;
            int pos;
            cbSrc--;
            if (cbSrc < 0) {
                RawPump();
                pbSrc = pbRaw;
                cbSrc = cbRaw - 1;
            }
            second = *pbSrc;
            pbSrc++;
            match = first + (second << 8);
            run = (match >> 13) + 2;
            pos = match & 0x1FFF;
            while (run >= 0) {
                window[cbOut] = window[pos & 0x1FFF];
                pos++;
                cbOut++;
                run--;
            }
        }
    }
    pbCur = window;
    if (full == 0) {
        cbCur = 0x2000;
        cbCarry = cbOut - 0x2000;
    } else {
        cbCur = cbOut;
        cbCarry = 0;
    }
    grfBits = bits;
    pbRaw = pbSrc;
    cbRaw = cbSrc;
}
