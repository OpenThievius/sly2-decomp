#include "blot.h"
#include "blotsprite.h"
#include "rgba.h"
struct AFF215850 { float a, b, c, d, e, f, u6, u7; } __attribute__((aligned(16)));
struct MovieChar215850 { u8 unknown_0x0[4]; int kind; BLOT *pblot; u8 unknown_0xC[4]; int index; };
struct Slot215850 { u8 unknown_0x0[0x58]; int iinst; };
extern "C" void UpdateSpriteInstance(float, BLOTSPRITE *, int, AFF215850 *, RGBA *, RGBA *);
extern "C" void func_00215850(MovieChar215850 *pchar, Slot215850 *slot, float dt, AFF215850 *xf, RGBA *rgbaAdd, RGBA *rgbaMul)
{
    if (pchar->kind == 4) {
        RGBA add = *rgbaAdd;
        RGBA mul = *rgbaMul;
        BLOTSPRITE *sprites = (BLOTSPRITE *)pchar->pblot->asprite;
        UpdateSpriteInstance(dt, &sprites[pchar->index], slot->iinst, xf, &add, &mul);
    }
}
