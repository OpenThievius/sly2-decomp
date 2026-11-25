#include "fbsprite.h"
extern "C" void func_002185F8(SPRITE *, int, int);
void func_002185D0(SPRITE *sprite)
{
    if (sprite->fRoot) func_002185F8(sprite, 0, 0);
}
