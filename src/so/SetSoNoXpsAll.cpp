// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
#include "oxa.h"
extern "C" {
void DiscardSoXps(SO *);
void SetSoNoXpsAll(SO *pso, s32 fNoXps) {
    OXA *poxa = pso->poxa;
    if (poxa != 0) {
        u64 fBit = fNoXps & 1;
        poxa->grf = (poxa->grf & ~4UL) | (fBit << 2);
        DiscardSoXps(pso);
    }
}
}
