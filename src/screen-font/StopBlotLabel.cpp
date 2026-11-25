#include "sly2.h"
struct BLOT;
struct VEnt { short delta; short idx; void (*fn)(void*, int, int, int, int, int); };
struct VEnt2 { short delta; short idx; void (*fn)(void*, int); };
struct VTab { u8 unknown_0x0[0x18]; VEnt e18; u8 unknown_0x20[0x88]; VEnt2 eA8; };
struct BLOT {
    u8 unknown_0x0[0xC]; VTab* vt; u8 unknown_0x10[0x6C];
    int unk7C; void* unk80; void* sprite84; int unk88;
    u8 unknown_0x8C[0x20]; int modal;
};
extern "C" void StopRootSprite(void*);
extern "C" void SetBlotModal(BLOT*, int);
extern "C" void StopBlotLabel(BLOT* pblot)
{
    StopRootSprite(pblot->sprite84);
    if (pblot->modal != 0)
        SetBlotModal(pblot, -1);
    pblot->vt->eA8.fn((char*)pblot + pblot->vt->eA8.delta, 0);
    pblot->vt->e18.fn((char*)pblot + pblot->vt->e18.delta, 6, 0, 0, 0, 0);
    pblot->unk88 = 0;
    pblot->unk7C = -1;
}
