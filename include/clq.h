/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CLQ, a quadratic g0 + g * (g1 + g * g2) (Sly 1's name, sly1 include/clq.h, CC0): ApplyAseg's speed from the "suck" value (InitAseg
   sets ASEG::clqSpeed to 1, 0, 0), ACT2's curves (LoadAloFromBrx reads 12 bytes into each), the sound system's fitted curves
   (FitClq fills SNDSYSTEM::fitA/fitB). LM, a range (gMin, gMax): ACT2's ranges (LoadAloFromBrx reads 8 bytes into each), ASEG::lmSpeed,
   a joystick axis's limits (SetJoyJoys resets four per stick to -0.75 and 0.75; GetJoyXYDeflection takes the array, retail's P2LM).
   crefboxes.h declares the CLQ a CRef of tag Clq boxes as one quadword (its copies use lq/sq): a source includes one or the other.
   C and C++. */
#ifndef SLY2_CLQ_H
#define SLY2_CLQ_H
#include "types.h"

struct CLQ {
    f32 g0, g1, g2;
};

struct LM {
    f32 gMin, gMax;
};
#endif
