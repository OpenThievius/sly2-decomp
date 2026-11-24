#include "so.h"
#include "sw.h"
/* the 0x30-byte render options block an SO points at (SO::field_0x134; func_001F3CC8 copies it whole) */
struct RO {
    u8 unknown_0x0[0xC];
    /* 0xC */ s32 field_0xC;   /* func_001F3C10: brought up to the world's field_0x3D60 after func_001A4478 */
    u8 unknown_0x10[0x20];
};
extern SW B_003DD490;
extern "C" void func_001A4478(SW *, int, RO *);
extern "C" void func_001F3C10(SO *self)
{
    RO *node = self->field_0x134;
    if (node != 0 && node->field_0xC != B_003DD490.field_0x3D60) {
        func_001A4478(&B_003DD490, 0, node);
        self->field_0x134->field_0xC = B_003DD490.field_0x3D60;
    }
}
