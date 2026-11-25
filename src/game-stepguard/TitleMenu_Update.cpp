#include "menu.h"
#include "joy.h"
#include "memcard.h"
#include "memcardmenu.h"
#include "pausemenu.h"
extern SAVE B_002E65E0;
extern "C" {
void Menu_Update(MENU *);
int FJoyButtonPressed(JOY *, int);
int FJoyButtonPeek(JOY *, int);
void ConsumeJoyButton(JOY *, int);
void func_001ACC38(MEMCARDMENU *, int);
void StartGameFromSave(SLOT *);
void StartNewGame(MENU *);
void OpenOptionsMenu(int);
int func_001A2C98();
void *PloFindSwObject_thunk(void *, int, int, int);
void func_001A2C48(int *, int **);
void *memset(void *, int, unsigned);
void PauseMenu_Push(PAUSEMENU *, int, PAUSEITEM *, PAUSEBLOT *, PAUSELABELS *);
void SelectLanguage(PAUSEITEM *);
extern MEMCARDMENU B_002E6550;
extern char B_003DD490[];
extern PAUSEMENU B_003D9ED0;
extern PAUSEITEM B_003DA578[];
extern int D_002C35B8[];
extern PAUSELABELS D_002C35F0;
}

void TitleMenu_Update(MENU *menu)
{
    Menu_Update(menu);
    if (menu->pblot == 0 || menu->pjoy == 0)
        return;
    if (FJoyButtonPressed(menu->pjoy, 0x800)) {
        SLOT *slot = B_002E65E0.pslotNewest;
        B_002E65E0.pslotCur = slot;
        if (slot != 0) {
            func_001ACC38(&B_002E6550, 1);
            StartGameFromSave(B_002E65E0.pslotCur);
        } else {
            StartNewGame(menu);
        }
        return;
    }
    if (FJoyButtonPeek(menu->pjoy, 0x100) && (menu->pjoy->grfbtnLatest & 0x108) == 0x100) {
        ConsumeJoyButton(menu->pjoy, 0x100);
        OpenOptionsMenu(0);
        return;
    }
    if (func_001A2C98() < 2)
        return;
    if (FJoyButtonPressed(menu->pjoy, 0x10)) {
        void *blot = PloFindSwObject_thunk(B_003DD490, 5, 0x5D6, 0);
        if (blot != 0) {
            int clanguage;
            int *ailanguage;
            func_001A2C48(&clanguage, &ailanguage);
            for (int ilanguage = 0; ilanguage < clanguage; ilanguage++) {
                int language = ailanguage[ilanguage];
                PAUSEITEM *item = &B_003DA578[ilanguage];
                memset(item, 0, 0x20);
                int kind = D_002C35B8[language];
                item->citemSub = language;
                item->pfnActivate = SelectLanguage;
                item->kind = kind;
            }
            PauseMenu_Push(&B_003D9ED0, clanguage, B_003DA578, (PAUSEBLOT *)blot, &D_002C35F0);
        }
    }
}
