#include "joy.h"
extern "C" void ClearVjoyPresses(JOY *, int);
extern "C" void ResetVjoy(JOY *vjoy)
{
    float zero = 0.0f;
    vjoy->uStick = zero;
    vjoy->radStick = zero;
    vjoy->yLeft = zero;
    vjoy->xLeft = zero;
    vjoy->field_0x2C = zero;
    vjoy->field_0x28 = zero;
    vjoy->field_0x24 = zero;
    vjoy->grfbtn = 0;
    vjoy->field_0x20 = zero;
    ClearVjoyPresses(vjoy, 0xFFFF);
}
