/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
struct SLOTROOT { int cslot; unsigned char *aslot; };
struct SPRITE { char pad[0x8]; unsigned char *ainst; };
struct BLOTSPRITES { char pad[0x84]; SPRITE *sprites; };
extern "C" {
void StopSpriteInstance(void);
void ClearSle(void *);
int IinstFindFreeSprite(void *);
void StartSpriteInstance(float, void *, int, int, void *, unsigned *, unsigned *);
int FStartSpriteLabelInstance(void);
}

int FStartSpriteLabelInstance(void *pblot, int isprite, int ilabel, int cslot, unsigned char *aslot)
{
    unsigned argbaAdd[4];
    unsigned argbaMul[4];
    if (aslot == 0) {
        SLOTROOT *pinstRoot = *(SLOTROOT **)(*(char **)((char *)pblot + 0x84) + 0x8);
        aslot = pinstRoot->aslot;
        cslot = pinstRoot->cslot;
    }
    for (int islot = 0; islot < cslot; islot++, aslot += 0x70) {
        unsigned char *pchar = *(unsigned char **)(aslot + 0x30);
        if (pchar == 0 || *(int *)(pchar + 0x4) != 4)
            continue;
        if (*(int *)(pchar + 0x10) == isprite) {
            StopSpriteInstance();
            ClearSle(aslot + 0x68);
            *(int *)(aslot + 0x58) = IinstFindFreeSprite(((char *)*(void **)((char *)pblot + 0x84) + isprite * 0x30));
            argbaAdd[0] = 0x7F7F7F7F;
            argbaMul[0] = 0xFFFFFFFF;
            StartSpriteInstance(0.0f, ((char *)*(void **)((char *)pblot + 0x84) + isprite * 0x30), ilabel, *(int *)(aslot + 0x58), aslot + 0x10, argbaAdd, argbaMul);
            return 1;
        }
        unsigned char *pinst = (unsigned char *)*(void **)((char *)*(void **)((char *)pblot + 0x84) + *(int *)(pchar + 0x10) * 0x30 + 0x8) + *(int *)(aslot + 0x58) * 0x18;
        if (FStartSpriteLabelInstance())
            return 1;
    }
    return 0;
}
