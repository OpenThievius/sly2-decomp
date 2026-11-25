#include "joy.h"
extern "C" {
extern float g_2dded0;
}
extern "C" void UpdateVjoyPressTimes(JOY *vjoy)
{
    s32 buttonsOld = vjoy->field_0x78;
    s32 buttonsNew = vjoy->grfbtn;
    float timeNow = g_2dded0;
    s32 buttonsPressed = buttonsNew & ~buttonsOld;
    vjoy->field_0x78 = buttonsNew;
    if (buttonsPressed != 0) {
        float *pressTime = vjoy->tButton;
        do {
            if (buttonsPressed & 1) {
                *pressTime = timeNow;
            }
            buttonsPressed >>= 1;
            pressTime++;
        } while (buttonsPressed != 0);
    }
    s32 leftIndex = 0;
    if (0.0f < vjoy->uStick) {
        leftIndex = 4;
    }
    char *leftSlot = (char *)vjoy->tStickLeft;
    *(float *)(leftSlot + leftIndex) = timeNow;
    s32 rightIndex = 0;
    if (0.0f < vjoy->field_0x2C) {
        rightIndex = 4;
    }
    char *rightSlot = (char *)vjoy->tStickRight;
    *(float *)(rightSlot + rightIndex) = timeNow;
}
