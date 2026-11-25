#include "fbsprite.h"
extern "C" void SeekSpriteInstanceTime(SPRITE *, int, int);
void func_00218038(SPRITE *sprite)
{
    if (sprite->fRoot) SeekSpriteInstanceTime(sprite, 0, 0);
}
