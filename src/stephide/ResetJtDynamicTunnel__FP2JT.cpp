#include "types.h"
extern "C" {
extern int D_002BF670;
struct Tunnel_194118 { u8 unknown_0x0[0xFC]; int f_fc, f_100; u8 unknown_0x104[4]; int f_108, f_10c, f_110; void *f_114; u8 unknown_0x118[8]; int f_120, f_124, f_128; u8 unknown_0x12C[4]; int f_130; u8 unknown_0x134[12]; int f_140; u8 unknown_0x144[0x20]; int f_164, f_168, f_16c; };
struct JT_194118 { u8 unknown_0x0[0x68]; Tunnel_194118 *tunnel; };
void ResetJtDynamicTunnel__FP2JT(JT_194118 *self) {
    Tunnel_194118 *t = self->tunnel;
    t->f_100 = 0;
    t->f_164 = 5;
    t->f_fc = 0;
    t->f_108 = 0;
    t->f_10c = 0;
    t->f_114 = &D_002BF670;
    t->f_110 = 1;
    t->f_120 = 0;
    t->f_168 = 1;
    t->f_128 = 3;
    t->f_124 = 0;
    t->f_16c = 0;
    t->f_130 = 0;
    t->f_140 = 0;
}
}
