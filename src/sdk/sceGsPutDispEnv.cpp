#include "types.h"
extern "C" {
struct DispEnv_240600 {
    u64 pmode;
    u64 smode2;
    u64 dispfb;
    u64 display;
    u64 bgcolor;
};
struct Mode_240600 {
    u8 unknown_0x0[6];
    short interlace;
};
Mode_240600 *func_002405F0();
void sceGsPutDispEnv(DispEnv_240600 *disp) {
    if (func_002405F0()->interlace == 1) {
        *(volatile u64 *)0x12000000 = disp->pmode;
        *(volatile u64 *)0x12000070 = disp->dispfb;
        *(volatile u64 *)0x12000080 = disp->display;
        *(volatile u64 *)0x120000C0 = disp->bgcolor;
    } else {
        *(volatile u64 *)0x12000000 = disp->pmode;
        *(volatile u64 *)0x12000020 = disp->smode2;
        *(volatile u64 *)0x12000090 = disp->dispfb;
        *(volatile u64 *)0x120000A0 = disp->display;
        *(volatile u64 *)0x120000E0 = disp->bgcolor;
    }
}
}
