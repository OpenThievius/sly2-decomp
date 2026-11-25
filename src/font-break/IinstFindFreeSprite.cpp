#include "sly2.h"
struct SPRITEINSTSLOT { u8 unknown_0x0[8]; s16 ilabel; u8 unknown_0xA[0x18 - 0xA]; };
struct SPRITEPOOL { u8 unknown_0x0[2]; u16 count; u8 unknown_0x4[4]; SPRITEINSTSLOT *ainst; };
extern "C" int IinstFindFreeSprite(SPRITEPOOL *ppool) {
    u16 count = ppool->count;
    int index = 0;
    if (count != 0) {
        SPRITEINSTSLOT *pinst = ppool->ainst;
        s16 *pilabel = &pinst->ilabel;
        do {
            if (*pilabel < 0) return index;
            index += 1;
            pilabel += sizeof(SPRITEINSTSLOT) / sizeof(s16);
        } while (index < (int)count);
    }
    return 0;
}
