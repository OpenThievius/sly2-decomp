// SPDX-License-Identifier: GPL-3.0-or-later
#include "jtzap.h"
extern "C" {
struct Continuation { long value; } __attribute__((packed));
s32 NewEmitter(int);
void SetEmitterUnpositioned(s32, int);
void SetJtZapState(JTZAP *, s32);
void SetZapContinuation(JTZAP *, long);
extern Continuation RO_002A6790;
void func_001A2028(JTZAP *pzap) {
    SetEmitterUnpositioned(NewEmitter(0x6A), 0);
    SetJtZapState(pzap, 6);
    SetZapContinuation(pzap, RO_002A6790.value);
}
}
