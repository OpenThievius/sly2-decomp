#include "sly2.h"
#include "memcard.h"
extern "C" {
int FSwLoadBusy(void *);
extern char B_003DD490[];
extern int g_2deb4c;
struct MENU { u8 unknown_0x0[0x44]; int phase; };
extern MENU B_002E6550;
extern float g_2ddf0c;
struct UL { s64 v; } __attribute__((packed));
extern const UL g_2a6ba0;
void CreateMemcardThread__FP7MEMCARDii(MEMCARD *, s64);
void func_001AB630(SAVE *, int);
void SetSaveState(SAVE *, int);
int func_001B42C0(void *);
int func_001B01E8(void *);
void MemcardMenu_SetState(MENU *, int);
extern char B_002F66B0[];
extern char B_003D9ED0[];
}
int FMemcardThreadValid(MEMCARD *);

void UpdateSave(SAVE *psave)
{
    if (FSwLoadBusy(B_003DD490) != 0) return;
    if (g_2deb4c != 0) return;
    if (B_002E6550.phase == 3) return;
    MEMCARD *pmc = &psave->mc;
    if (FMemcardThreadValid(pmc) != 0) return;
    if (psave->state == psave->cardState) {
        if (psave->tNext <= g_2ddf0c)
            CreateMemcardThread__FP7MEMCARDii(pmc, g_2a6ba0.v);
        else
            func_001AB630(psave, psave->cardState);
    } else {
        SetSaveState(psave, psave->cardState);
    }
    if (FMemcardThreadValid(&psave->mc) != 0) return;
    if (func_001B42C0(B_002F66B0) != 0) return;
    int phase = B_002E6550.phase;
    if (phase != 1) return;
    if (0.3f <= g_2ddf0c - psave->tStamp) {
        if (func_001B01E8(B_003D9ED0) != 0) {
            if (psave->state != 6)
                MemcardMenu_SetState(&B_002E6550, 0x2E);
            return;
        }
        switch (psave->state) {
        case 1: MemcardMenu_SetState(&B_002E6550, 0x11); break;
        case 2: MemcardMenu_SetState(&B_002E6550, 0x12); break;
        case 3: MemcardMenu_SetState(&B_002E6550, 0x15); break;
        case 4: MemcardMenu_SetState(&B_002E6550, 0x18); break;
        }
    }
}
