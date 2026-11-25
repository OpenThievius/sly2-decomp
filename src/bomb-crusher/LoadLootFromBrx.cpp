#include "loot.h"
#include "alloc.h"
extern "C" void * CStackFrame_Construct(void *);
extern "C" void *PvAllocStackClearImpl__Fi(ALLOCREQ *);
extern "C" void CSo_LoadFromBrx(LOOT *, void *);
extern "C" void func_0013C440(LOOT *);
extern "C" void *PvAllocSwCopyImpl__FiPv(ALLOCREQ *, void *);
extern "C" void CStackFrame_Destructor(void *, int);
void LoadLootFromBrx(LOOT *loot, void *bis)
{
    char frame[0x10];
    int align = 0x10;
    CStackFrame_Construct(frame);
    ALLOCREQ req;
    ALLOCREQ *preq = &req;
    req.cb = 0x580;
    preq->cbAlign = align;
    loot->alootdef = (LOOTDEF *)PvAllocStackClearImpl__Fi(preq);
    CSo_LoadFromBrx(loot, bis);
    func_0013C440(loot);
    req.cb = loot->clootdef * 0x2C;
    preq->cbAlign = align;
    loot->alootdef = (LOOTDEF *)PvAllocSwCopyImpl__FiPv(preq, loot->alootdef);
    CStackFrame_Destructor(frame, 2);
}
