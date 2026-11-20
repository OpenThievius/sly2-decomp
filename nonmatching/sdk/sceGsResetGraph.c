// SPDX-License-Identifier: GPL-3.0-or-later
typedef short s16;
typedef int s32;
typedef unsigned long u64;

typedef struct GsCrtState {
    s16 interlace;
    s16 mode;
    s16 ffmode;
    s16 revision;
    s32 handlerId;
    s32 handlerCookie;
} GsCrtState;

void GsPutIMR(s32);
void RemoveIntcHandler(s32, s32);
void SetGsCrt(s32, s32, s32);
void func_00235110(s32);
GsCrtState *func_002405F0(void);

void sceGsResetGraph(s16 mode, s16 interlace, s16 ffmode, s16 flag) {
    GsCrtState *state;
    switch (mode) {
    case 0:
        state = func_002405F0();
        *(volatile u64 *)0x12001000 = 0x200;
        state->interlace = interlace;
        state->mode = ffmode;
        state->revision = (*(volatile u64 *)0x12001000 >> 16) & 0xFF;
        GsPutIMR(0xFF00);
        state->ffmode = (flag != 0);
        if (state->handlerId != 0) {
            func_00235110(2);
            RemoveIntcHandler(2, state->handlerCookie);
            state->handlerCookie = 0;
            state->handlerId = 0;
        }
        SetGsCrt(interlace & 1, ffmode & 0xFF, flag & 1);
        return;
    case 1:
        *(volatile u64 *)0x12001000 = 0x100;
        return;
    case 5:
        state = func_002405F0();
        state->ffmode = (flag != 0);
        state->interlace = interlace;
        state->mode = ffmode;
        state->revision = (*(volatile u64 *)0x12001000 >> 16) & 0xFF;
        SetGsCrt(interlace & 1, ffmode & 0xFF, flag & 1);
        return;
    default:
        return;
    }
}
