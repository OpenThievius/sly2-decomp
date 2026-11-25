#include "cref.h"
#include "sw.h"
#include "memcard.h"
#include "memcardmenu.h"
extern "C" SW B_003DD490;
extern "C" char B_003D4A60[];
extern "C" MEMCARDMENU B_002E6550;
extern "C" char B_002E65A0[];
extern int g_2deb4c;
extern "C" {
int FSwLoadBusy(void *);
int IEpisodeCurrent(void);
CRef RefGetGameSaveValue(void *, void *);
void CRef_Destruct(CRef *);
void MemcardMenu_SetState(void *, int);
void func_001ABCE8(void *);
void BusyMenu_Show(void *);
}

extern "C" void TryAutosave(SAVE *psave, int fForce)
{
    if (psave->pslotCur != 0) {
        if (FSwLoadBusy(&B_003DD490) == 0 && g_2deb4c == 0) {
            if (IEpisodeCurrent() != 0 || fForce != 0) {
                int n = RefGetGameSaveValue(B_003DD490.psavepathAutosaveWarned, B_003D4A60).m_tag.m_n;
                if (n == 0) {
                    B_002E6550.mode = 3;
                    MemcardMenu_SetState(&B_002E6550, 0x22);
                } else {
                    func_001ABCE8(psave);
                    BusyMenu_Show(B_002E65A0);
                }
            }
        }
    }
}
