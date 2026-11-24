#include "types.h"
/* the allocator a blot's palloc points at (retail's vtable pointer at 0, first virtual in slot 1) */
struct BLOTALLOC {
    virtual void *Alloc(s32 size, s32 align);
};
/* the blot's fields this function reads (blot.h's BLOT: palloc at 0xC4) */
struct BLOTBUFFER {
    u8 unknown_0x0[0xC4];
    BLOTALLOC *palloc;
    u8 unknown_0xC8[0x30];
    s128 *pqwBuffer;
};
extern "C" {
void func_00213C68(BLOTBUFFER *blot, s128 *source) {
    if (blot->pqwBuffer == 0) {
        blot->pqwBuffer = (s128 *)blot->palloc->Alloc(0x20, 0x1F);
    }
    s128 *dst = blot->pqwBuffer;
    dst[0] = source[0];
    dst[1] = source[1];
}
}
