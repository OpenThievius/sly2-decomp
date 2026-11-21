#include "cref.h"
struct ITEM { int index; int b; };
struct SHOP { char pad0[0x40]; int mode; int pad44; int count; ITEM items[0x41]; };
extern "C" {
int FGadgetAcquired(int);
int FGadgetOnSale(int);
void ShopMenu_Select(SHOP *, int);
CRef func_001D8A38(const char *, const char *, char *, int);
int sprintf(char *, const char *, ...);
extern const char RO_002A79A0[];
extern const char RO_002A79D0[];
extern const char RO_002A79D8[];
void ShopMenu_BuildList(SHOP *menu)
{
    for (int clear = 0; clear < menu->count; clear++)
        menu->items[clear].index = -1;
    int mode = menu->mode;
    menu->count = 0;
    switch (mode) {
    case 0: {
        int index = 7;
        while (index < 0x2B) {
            if (FGadgetOnSale(index) != 0 && FGadgetAcquired(index) == 0) {
                unsigned int count = menu->count;
                if (count >= 0x41)
                    break;
                menu->items[count].index = index;
                menu->count = count + 1;
            }
            index++;
        }
        break;
    }
    case 1: {
        for (int index = 0; index < 0x40; index++) {
            CRef ref;
            char name[0x20];
            ref.m_tagk = TAGK_Nil;
            sprintf(name, RO_002A79A0, index);
            ref = func_001D8A38(RO_002A79D0, RO_002A79D8, name, 0);
            if (ref.m_tag.m_n == 0)
                continue;
            unsigned int count = menu->count;
            if (count >= 0x41)
                break;
            menu->items[count].index = index;
            menu->count = count + 1;
        }
        break;
    }
    }
    ShopMenu_Select(menu, *(int *)((char *)menu + 0x24C));
}
}
