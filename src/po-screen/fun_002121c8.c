#include "types.h"
/* a C view of blot.h's BLOT (C++ only): the fields this function reads, by the shared names (blots 0x58, field_0x64) */
typedef struct BLOT {
    u8 unknown_0x0[0x58];
    s32 blots;
    u8 unknown_0x5C[0x8];
    s32 field_0x64;
} BLOT;
extern f32 g_2ddf0c;
s32 func_002121C8(BLOT *arg0) {
    s32 var_v1;
    var_v1 = 0;
    if (arg0->blots < 2) {
        var_v1 = arg0->field_0x64 < 2;
    }
    return var_v1;
}
