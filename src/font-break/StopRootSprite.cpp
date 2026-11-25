#include "fbsprite.h"
extern "C" void StopSpriteInstance(SPRITE *, int);
void StopRootSprite(SPRITE *sprite)
{
    if (sprite->fRoot) StopSpriteInstance(sprite, 0);
}
