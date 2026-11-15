#include "cref.h"
struct MENU { char pad[0x40]; int state; char pad2[8]; int mode; };
extern "C" {
extern char B_003DA530[];
extern char B_003D9ED0[];
extern int B_002E65E0;
extern int B_003D4A60;
extern void *B_003E0FE4;
int CGc_FFindScreen(void *);
int func_001B0160(void *);
int func_001B0108(void *);
void MemcardMenu_ClearState(MENU *);
void func_001ACC38(MENU *, int);
void PauseMenu_Close(void *);
void PauseMenu_Pop(void *);
void StartNewGame(void *);
void MemcardMenu_SetState(MENU *, int);
void func_001ABD40(int *);
CRef RefSetGameSaveValue(void *, const CRef &, int *);
}

static inline void SetSaveBool(void *path, int fBool)
{
    CRef value;
    value.m_tag.m_bool = fBool != 0;
    value.m_tagk = TAGK_Bool;
    CRef copy(value);
    RefSetGameSaveValue(path, copy, &B_003D4A60);
}

void func_001ACFE0(MENU *pmenu)
{
    switch (pmenu->state) {
    case 0x11:
    case 0x12:
    case 0x15:
    case 0x18:
        if (CGc_FFindScreen(B_003DA530) != 0) {
            if (func_001B0160(B_003D9ED0) != 0) {
                MemcardMenu_ClearState(pmenu);
                func_001ACC38(pmenu, 2);
                PauseMenu_Close(B_003D9ED0);
                StartNewGame(B_003DA530);
                return;
            }
        }
    case 0x14:
    case 0x17:
    case 0x1D:
    case 0x23:
    case 0x24:
    case 0x2E:
        MemcardMenu_ClearState(pmenu);
        func_001ACC38(pmenu, 2);
        if (func_001B0108(B_003D9ED0) != 0)
            PauseMenu_Pop(B_003D9ED0);
        break;
    case 0x1B:
    case 0x1C:
    case 0x20:
        MemcardMenu_ClearState(pmenu);
        break;
    case 0x22:
        SetSaveBool(B_003E0FE4, 1);
        if (pmenu->mode < 4) {
            if (pmenu->mode > 0) {
                MemcardMenu_SetState(pmenu, 0x1A);
                func_001ABD40(&B_002E65E0);
            }
        }
        break;
    }
}
// variant
