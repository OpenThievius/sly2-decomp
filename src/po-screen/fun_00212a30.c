#include "types.h"
/* a C view of blot.h's BLOT (C++ only): the fields this function reads, by the shared names (blots 0x58, time 0x5C) */
typedef struct BLOT {
    u8 unknown_0x0[0x58];
    s32 blots;
    f32 time;
} BLOT;
extern f32 g_2ddf0c;
void func_00212A30(BLOT *arg0) {
    if (arg0->blots == 2) {
        arg0->time = g_2ddf0c;
    }
}
