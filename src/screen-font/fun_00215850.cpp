#include "rgba.h"
struct AFF215850 { float a, b, c, d, e, f, u6, u7; } __attribute__((aligned(16)));
struct Sprite215850;
struct MovieChar215850 { char pad0[4]; int kind; Sprite215850 *base8; char padC[4]; int index; };
struct Slot215850 { char pad0[0x58]; int iinst; };
extern "C" void UpdateSpriteInstance(float, Sprite215850 *, int, AFF215850 *, RGBA *, RGBA *);
extern "C" void func_00215850(MovieChar215850 *pchar, Slot215850 *slot, float dt, AFF215850 *xf, RGBA *rgbaAdd, RGBA *rgbaMul)
{
    if (pchar->kind == 4) {
        RGBA add = *rgbaAdd;
        RGBA mul = *rgbaMul;
        Sprite215850 *sprites = *(Sprite215850 **)((char *)pchar->base8 + 0x84);
        UpdateSpriteInstance(dt, (Sprite215850 *)((char *)sprites + pchar->index * 0x30), slot->iinst, xf, &add, &mul);
    }
}
