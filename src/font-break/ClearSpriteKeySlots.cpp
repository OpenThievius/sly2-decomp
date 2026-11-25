#include "sly2.h"
struct DEPTHSLOT { u8 unknown_0x0[0x30]; void *pchar; u8 unknown_0x34[0x3C]; };
struct SPRITEKEY { u8 unknown_0x0[6]; unsigned char cclear; u8 unknown_0x7[13]; unsigned short *aclear; u8 unknown_0x18[8]; };
struct LABELINST { u8 unknown_0x0[4]; DEPTHSLOT *aslot; u8 unknown_0x8[0x10]; };
struct SPRITELABEL { u8 unknown_0x0[4]; SPRITEKEY *akey; u8 unknown_0x8[8]; struct { u8 unknown_0x0[8]; LABELINST *ainst; } *pinfo; };
extern "C" {
void func_002158C0(void *, DEPTHSLOT *);
void InitDepthSlot(DEPTHSLOT *);
void ClearSpriteKeySlots(SPRITELABEL *plabel, int ikey, int iinst)
{
    SPRITEKEY *pkey = &plabel->akey[ikey];
    DEPTHSLOT *aslot = plabel->pinfo->ainst[iinst].aslot;
    for (int iclear = 0; iclear < pkey->cclear; iclear++) {
        DEPTHSLOT *pslot = &aslot[pkey->aclear[iclear]];
        if (pslot->pchar != 0)
            func_002158C0(pslot->pchar, pslot);
        else
            InitDepthSlot(pslot);
    }
}
}
