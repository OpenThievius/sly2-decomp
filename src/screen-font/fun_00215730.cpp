#include "fbsprite.h"

extern "C" int IinstFindFreeSprite(void *);
extern "C" void PlaceSpriteInstance(void *, int, int, void *, RGBA *, RGBA *);
extern "C" void *func_001BEED8(int);
extern "C" ROGWINDOW *func_001BEB28(void *);

extern "C" void func_00215730(MOVIECHAR *chr, SLOT *slot, void *xf, RGBA *add, RGBA *mul)
{
    slot->pchar = chr;
    switch (chr->type) {
    case 4: {
        int iinst = IinstFindFreeSprite(&((SPRITE *)chr->pblot->asprite)[chr->id]);
        slot->iinst = iinst;
        RGBA localAdd = *add;
        RGBA localMul = *mul;
        PlaceSpriteInstance(&((SPRITE *)chr->pblot->asprite)[chr->id], 0x314, iinst, xf, &localAdd, &localMul);
        break;
    }
    case 6:
        if (chr->id != -1) {
            void *object = func_001BEED8(chr->id);
            if (object) chr->pwindow = func_001BEB28(object);
        }
        break;
    }
}
