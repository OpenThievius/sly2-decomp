// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
struct B8 { char b[8]; };
struct Vec12_204D48 { B8 head; int tail; };
/* local view: STEP (step.h) has no fields at 0x1F0 to 0x1FC but one (field_0x1F4, read by bevy_player_input_from_pad_cm under another name) */
struct Step204D48 {
    u8 unknown_0x0[0x1F0];
    float spinRatio;
    float spinX;
    float spinY;
    float spinZ;
};
// Sqrt: sqrt.s with an early-clobber output (=&f). Measured on every sqrt.s user (16 sources): none gets worse, six get closer, two reach 0 (a third holds VU0 asm and stays out);
// retail's helper keeps the result out of the operand's register. The one Sqrt helper form (docs/contributing/exceptions.md).
static inline float Sqrt(float x) { float r; asm volatile("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
extern "C" const Vec12_204D48 D_002C3CB8;
extern "C" void SetStepSpinRatio__FP4STEPf(Step204D48 *step, float ratio)
{
    *(Vec12_204D48 *)&step->spinX = D_002C3CB8;
    step->spinX = step->spinX * ratio;
    step->spinY = step->spinY * ratio;
    float root = Sqrt(ratio);
    float inverse = 1.0f / root;
    step->spinRatio = ratio;
    step->spinZ = step->spinZ * inverse;
}
