#include "fbsprite.h"
extern "C" void SeekSpriteInstanceFraction(SPRITE *, int, int);
void func_00217FB8(SPRITE *sprite)
{
    if (sprite->fRoot) SeekSpriteInstanceFraction(sprite, 0, 0);
}
