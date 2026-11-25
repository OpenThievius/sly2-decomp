#include "types.h"

typedef struct BLOTMOVIE {
    u8 unknown_0x0[0x44];
    s32 field_0x44;
    s32 field_0x48;
} BLOTMOVIE;

typedef struct BLOT {
    u8 unknown_0x0[0xC];
    s32 *field_0xC;
    u8 unknown_0x10[0x40];
    s32 field_0x50;
    s32 field_0x54;
    s32 field_0x58;
    f32 field_0x5C;
    u8 unknown_0x60[0x4];
    s32 field_0x64;
    f32 field_0x68;
    u8 unknown_0x6C[0xC];
    s32 field_0x78;
    u8 unknown_0x7C[0x4];
    s16 field_0x80;
    u8 unknown_0x82[0x2];
    s32 field_0x84;
    u8 unknown_0x88[0x20];
    s32 field_0xA8;
    u8 unknown_0xAC[0x14];
    BLOTMOVIE *field_0xC0;
    u8 unknown_0xC4[0x34];
    s32 field_0xF8;
    char field_0xFC[0x14];
    s32 field_0x110;
    s32 field_0x114;
    s32 field_0x118;
    s32 field_0x11C;
    s32 field_0x120;
} BLOT;

extern f32 g_2ddf0c;

void SetTimerTimers__FP5TIMER6TIMERS(BLOT *arg0, s32 arg1) {
    if (arg0->field_0x64 != arg1) {
        arg0->field_0x64 = arg1;
        arg0->field_0x68 = g_2ddf0c;
    }
}
