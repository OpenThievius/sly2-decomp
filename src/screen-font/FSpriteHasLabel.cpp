#include "blotsprite.h"
#define NULL 0
s32 FSpriteHasLabel(s32 arg0, BLOTSPRITE *sprite, s32 label) {
    s32 i;
    s32 *pid;
    if (label == -1) return 0;
    i = 0;
    if (i < sprite->clabel) {
        pid = &sprite->alabel->id;
        do {
            i++;
            if (label == *pid) return 1;
            pid += sizeof(BLOTSPRITELABEL) / sizeof(s32);
        } while (i < sprite->clabel);
    }
    return 0;
}
