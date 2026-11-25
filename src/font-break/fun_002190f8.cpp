#include "fbsprite.h"
extern "C" void PauseSpriteInstance(SPRITE *, int);
extern "C" void func_002190F8(SPRITELABEL *plabel, int ikey, int iinst)
{
    SPRITEKEY *pkey = &plabel->akey[ikey];
    for (int iaction = 0; iaction < pkey->caction; iaction++) {
        if (pkey->aaction[iaction] == 7)
            PauseSpriteInstance(plabel->psprite, iinst);
    }
}
