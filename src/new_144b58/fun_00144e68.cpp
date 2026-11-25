#include "types.h"
#include "goal.h"
struct Dst_144E68 : GOAL { u8 unknown_0x30[0x10]; int i40; u8 unknown_0x44[0x20]; float f64; u8 unknown_0x68[0x64]; int iCC; float fD0; };
struct Src_144E68 : GOAL { int i30; float f34; int i38; float f3C; s128 v40; };
extern "C" {
void GoalGotoPos_SetPos(Src_144E68 *, s128);
void func_001EEF70();
Dst_144E68 *func_00205438(STEP *, int);
void func_00144E68(Src_144E68 *src) {
    func_001EEF70();
    Dst_144E68 *dst = func_00205438(src->pstep, 0xA8);
    dst->i40 = src->i30;
    dst->f64 = src->f34;
    dst->iCC = src->i38;
    dst->fD0 = src->f3C;
    GoalGotoPos_SetPos(src, src->v40);
    dst->Activate();
}
}
