#include "shopmenu.h"
extern SHOPMENU B_003DA150;
extern char B_003DD490;
extern char B_002DEB30;
extern GADGETDEF D_002BCD00[];
extern LOOTROW D_002C3288[];
extern "C" const char RO_002A7A38[];
extern "C" int sprintf(char *, const char *, ...);
extern "C" char *strcpy(char *, const char *);
extern "C" int GetGameCoins(void *);
const char *PchzStringFromId(void *, int);

void func_001DCAB0(char *pchz)
{
    if (B_003DA150.dialogKind != -1) {
        strcpy(pchz, PchzStringFromId(&B_003DD490, B_003DA150.dialogArg));
    } else {
        switch (B_003DA150.mode) {
        case 0: {
            unsigned gadget = B_003DA150.idGadget;
            if (gadget < 0x2B && D_002BCD00[gadget].sidDesc != -1) {
                int *pprice = &D_002BCD00[gadget].price;
                int coins = GetGameCoins(&B_002DEB30);
                int sidAfford = coins < *pprice ? 0xD9 : 0xDA;
                sprintf(pchz, RO_002A7A38, PchzStringFromId(&B_003DD490, D_002BCD00[gadget].sidName),
                        PchzStringFromId(&B_003DD490, D_002BCD00[gadget].sidDesc), PchzStringFromId(&B_003DD490, sidAfford));
                return;
            }
            strcpy(pchz, PchzStringFromId(&B_003DD490, 0xDC));
            break;
        }
        case 1: {
            unsigned loot = B_003DA150.idLoot;
            if (loot < 0x40) {
                const char *pchzFormat = PchzStringFromId(&B_003DD490, 0xDB);
                sprintf(pchz, pchzFormat, D_002C3288[loot].price);
                return;
            }
            strcpy(pchz, PchzStringFromId(&B_003DD490, 0xE3));
            break;
        }
        default:
            pchz[0] = 0;
            return;
        }
    }
}
