/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CHN and ANIMCURVE: what PchnFindAseg returns for an animation channel (func_00204E38 and func_00204ED8 read it; our names, from what the two do).
   A CHN holds the curve at 0x4; the curve is an object whose vtable pointer is its first word and whose slot 3 evaluates it at a time and rate. C++ only. */
#ifndef SLY2_CHN_H
#define SLY2_CHN_H
#include "types.h"

struct ANIMCURVE {
    virtual void Slot1();
    virtual void Slot2();
    virtual void Eval(float t, float rate, QW *pqwPos, QW *pqwVel); /* 3: both functions call it, passing the channel's time, the handle's svt and a result vector */
};

struct CHN {
    u8 unknown_0x0[0x4];
    /* 0x4 */ ANIMCURVE *curve;
};
#endif
