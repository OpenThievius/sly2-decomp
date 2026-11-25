// SPDX-License-Identifier: GPL-3.0-or-later
#include "cref.h"
#include "shopmenu.h"
#include "joy.h"
extern "C" {
int FJoyButtonPressed(JOY *, int);
int GetGameCoins(void *);
void Menu_SetDialog(MENU *, int, int);
void Menu_Update(void);
void Menu_UpdateStick(MENU *);
void *NewEmitter(int);
void SetEmitterUnpositioned(void *, void *);
void SetGadgetAcquired(int, int);
void SetGameCoins(void *, int);
void ShopMenu_BuildList(SHOPMENU *);
void ShopMenu_SetPage(SHOPMENU *, int);
void ShopMenu_UpdateBlot(SHOPMENU *);
void func_0019F0A8(void *);
CRef func_001D8A38(const char *, const char *, char *, int);
CRef func_001D8B20(const CRef &, const char *, const char *, char *, int);
int sprintf(char *, const char *, ...);
extern char B_002DEB30[];
extern char B_003DD490[];
extern GADGETDEF D_002BCD00[];
extern LOOTROW D_002C3288[];
extern const char RO_002A79A0[];
extern const char RO_002A79D0[];
extern const char RO_002A79D8[];
void ShopMenu_Update(SHOPMENU *menu)
{
    Menu_Update();
    if (menu->mode == -1)
        return;
    JOY *pjoy = menu->pjoy;
    if (pjoy == 0)
        return;
    if (menu->dialogKind != 0 && FJoyButtonPressed(pjoy, 0x10)) {
        ShopMenu_SetPage(menu, -1);
        return;
    }
    switch (menu->mode) {
    case 0:
        if (FJoyButtonPressed(menu->pjoy, 0x40)) {
            int selected = menu->idGadget;
            if (selected == -1) {
                SetEmitterUnpositioned(NewEmitter(0x36), 0);
            } else {
                int price = D_002BCD00[selected].price;
                int coins = GetGameCoins(B_002DEB30);
                if (menu->dialogKind == 0) {
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
        if (FJoyButtonPressed(menu->pjoy, 0x40)) {
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
                    SetGameCoins(B_002DEB30, GetGameCoins(B_002DEB30) + D_002C3288[menu->idLoot].price);
                    ShopMenu_BuildList(menu);
                    SetEmitterUnpositioned(NewEmitter(0x29), 0);
                }
            }
        }
        break;
    }
    if (menu->dialogKind == 0) {
        if (FJoyButtonPressed(menu->pjoy, 0x10))
            Menu_SetDialog(menu, -1, -1);
    }
    if (FJoyButtonPressed(menu->pjoy, 0x80)) {
        Menu_SetDialog(menu, -1, -1);
        ShopMenu_SetPage(menu, menu->mode == 0);
    }
    if (menu->dialogKind != 0)
        Menu_UpdateStick(menu);
    ShopMenu_UpdateBlot(menu);
}
}
