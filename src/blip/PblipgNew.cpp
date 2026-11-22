// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "blip.h"
/* BLIPG's first words as retail's allocator writes them: BASIC's two cleared fields, then the vtable pointer (a class's constructor
   would set it; the vtable at 0x2CB5D8 is game data, so it is stored as a pointer) */
struct BLIPGHEAD {
    s32 field_0x0;
    s32 field_0x4;
    s32 field_0x8;
    void *pvtable;
};
extern char D_002CB5D8;
extern "C" {
void *PvAllocSlotheapImpl(SLOTHEAP *);
void *PdlFromSwCid(SW *, int);
void AppendSlEntry(void *, void *);
}
BLIPG *PblipgNew(SW *psw)
{
    if (psw->slotheapBlipg.pslotFree == 0) {
        if (psw->slotheapBlipg.pblockCur != 0)
            return 0;
    }
    BLIPG *pblipg = (BLIPG *)PvAllocSlotheapImpl(&psw->slotheapBlipg);
    memset(pblipg, 0, 0x460);
    BLIPGHEAD *phead = (BLIPGHEAD *)pblipg;
    phead->field_0x0 = 0;
    phead->field_0x4 = 0;
    phead->pvtable = &D_002CB5D8;
    int i = 31;
    do {
    } while (--i != -1);
    AppendSlEntry(PdlFromSwCid(psw, 0x1C), pblipg);
    pblipg->Init();
    pblipg->AddHierarchy();
    pblipg->PostLoad();
    return pblipg;
}
