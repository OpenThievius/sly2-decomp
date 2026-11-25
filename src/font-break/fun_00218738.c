#include "types.h"

/* a C view of fbsprite.h's SPRITE (C++ only): the instance list at 8, an instance's paused flag at 0x10 */
typedef struct SPRITEINST218738 {
    u8 unknown_0x0[0x10];
    s32 fPaused;
} SPRITEINST218738;

typedef struct SPRITE218738 {
    u8 unknown_0x0[8];
    SPRITEINST218738 *insts;
} SPRITE218738;

s32 func_00218738(SPRITE218738 *sprite) {
    return sprite->insts->fPaused;
}
