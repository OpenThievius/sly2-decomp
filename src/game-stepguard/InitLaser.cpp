#include "types.h"
/* a laser seen as an LO (lo.h: the word at 0x40 is its grf flags or its world-table entry), with the 64-bit word at 0x148 no other source reads */
struct Laser { u8 unknown_0x0[0x40]; int f40; u8 unknown_0x44[0x148 - 0x44]; s64 f148; u8 unknown_0x150[0x1C0 - 0x150]; float f1C0; };
extern "C" void func_001DE2A0(Laser *);
extern "C" void InitLaser(Laser *self) {
    func_001DE2A0(self);
    int link = self->f40;
    self->f1C0 = 1.0f;
    self->f148 = self->f148 & ~(1L << 35);
    if ((link ^ 1) & 1) {
        *(int *)link = *(int *)link | 8;
        return;
    }
    self->f40 = link | 8;
}
