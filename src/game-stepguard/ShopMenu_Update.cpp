// SPDX-License-Identifier: GPL-3.0-or-later
#include "cref.h"
#include "shopmenu.h"
struct COINBAG { int amount; int b; int c; };
extern "C" {
int FJoyButtonPressed(void *, int);
int GetGameCoins(void *);
void Menu_SetDialog(void *, int, int);
void Menu_Update(void);
void Menu_UpdateStick(void *);
void *NewEmitter(int);
void SetEmitterUnpositioned(void *, void *);
void SetGadgetAcquired(int, int);
void SetGameCoins(void *, int);
void ShopMenu_BuildList(void *);
void ShopMenu_SetPage(void *, int);
void ShopMenu_UpdateBlot(void *);
void func_0019F0A8(void *);
CRef func_001D8A38(const char *, const char *, char *, int);
CRef func_001D8B20(const CRef &, const char *, const char *, char *, int);
int sprintf(char *, const char *, ...);
extern char B_002DEB30[];
extern char B_003DD490[];
extern GADGETDEF D_002BCD00[];
extern COINBAG D_002C3288[];
extern const char RO_002A79A0[];
extern const char RO_002A79D0[];
extern const char RO_002A79D8[];
void ShopMenu_Update(SHOPMENU *menu)
{
    Menu_Update();
    if (menu->mode == -1)
        return;
    void *dev = menu->dev;
    if (dev == 0)
        return;
    if (menu->dialog != 0 && FJoyButtonPressed(dev, 0x10)) {
        ShopMenu_SetPage(menu, -1);
        return;
    }
    switch (menu->mode) {
    case 0:
        if (FJoyButtonPressed(menu->dev, 0x40)) {
            int selected = menu->idGadget;
            if (selected == -1) {
                SetEmitterUnpositioned(NewEmitter(0x36), 0);
            } else {
                int price = D_002BCD00[selected].price;
                int coins = GetGameCoins(B_002DEB30);
                if (menu->dialog == 0) {
                    Menu_SetDialog(menu, -1, -1);
                    SetGameCoins(B_002DEB30, coins - price);
                    SetGadgetAcquired(menu->idGadget, 1);
                    ShopMenu_BuildList(menu);
                    SetEmitterUnpositioned(NewEmitter(0x29), 0);
                    func_0019F0A8(B_003DD490);
                } else if (coins >= price) {
                    Menu_SetDialog(menu, 0, 0x34);
                } else {
                    Menu_SetDialog(menu, 1, 0x35);
                }
            }
        }
        break;
    case 1:
        if (FJoyButtonPressed(menu->dev, 0x40)) {
            int slot = menu->idLoot;
            if (slot == -1) {
                SetEmitterUnpositioned(NewEmitter(0x36), 0);
            } else {
                CRef ref;
                char name[0x20];
                ref.m_tagk = TAGK_Nil;
                sprintf(name, RO_002A79A0, slot);
                ref = func_001D8A38(RO_002A79D0, RO_002A79D8, name, 0);
                if (ref.m_tag.m_n > 0) {
                    func_001D8B20(CRef(ref.m_tag.m_n - 1, TAGK_S32), RO_002A79D0, RO_002A79D8, name, 0);
                    SetGameCoins(B_002DEB30, GetGameCoins(B_002DEB30) + D_002C3288[menu->idLoot].amount);
                    ShopMenu_BuildList(menu);
                    SetEmitterUnpositioned(NewEmitter(0x29), 0);
                }
            }
        }
        break;
    }
    if (menu->dialog == 0) {
        if (FJoyButtonPressed(menu->dev, 0x10))
            Menu_SetDialog(menu, -1, -1);
    }
    if (FJoyButtonPressed(menu->dev, 0x80)) {
        Menu_SetDialog(menu, -1, -1);
        ShopMenu_SetPage(menu, menu->mode == 0);
    }
    if (menu->dialog != 0)
        Menu_UpdateStick(menu);
    ShopMenu_UpdateBlot(menu);
}
}
