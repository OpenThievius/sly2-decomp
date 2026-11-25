#include "fbsprite.h"
int func_00218710(SPRITE *sprite)
{
    SPRITEINST *inst = sprite->insts;
    if (inst->ilabel != 0) {
        if (inst->fPaused == 0) return 1;
    }
    return 0;
}
