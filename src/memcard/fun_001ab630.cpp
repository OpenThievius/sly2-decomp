#include "types.h"
#include "memcard.h"
extern "C" {
extern int g_savedata_3e0ea8;
void SetMemcardThreadHighPrio__FP7MEMCARD(MEMCARD *);
int ValidateSaveSlot(SAVE *, SLOT *);
void SetSaveState(SAVE *, int);
}
void func_001AB630(SAVE *psave)
{
    if (psave->state == 5 && g_savedata_3e0ea8 != 0) {
        SLOT *pslot = psave->aslot;
        SetMemcardThreadHighPrio__FP7MEMCARD(&psave->mc);
        for (int index = 2; index >= 0; index--, pslot++)
            ValidateSaveSlot(psave, pslot);
        psave->cardState = 6;
        SetSaveState(psave, 6);
    }
}
