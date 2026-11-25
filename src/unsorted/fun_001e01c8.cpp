#include "types.h"
struct JSG { u8 unknown_0x0[0x50]; s32 phase; u8 unknown_0x54[4]; s32 value; u8 unknown_0x5C[0x24]; s32 flag; };
extern "C" void func_001E01C8(JSG *jsg, int value)
{
    if (value > 0) {
        if (value < 0x200) {
            if (jsg->phase < 2) {
                jsg->value = value;
                jsg->flag = 1;
            }
        }
    }
}
