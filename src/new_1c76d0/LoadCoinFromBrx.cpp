#include "sly2.h"
#include "alloc.h"
#include "coin.h"
extern "C" void *CStackFrame_Construct(void *);
extern "C" void *PvAllocStackImpl__Fi(ALLOCREQ *);
extern "C" void LoadDprizeFromBrx(COIN *, void *);
extern "C" void func_001C7A08(COIN *);
extern "C" void *PvAllocSwCopyImpl__FiPv(ALLOCREQ *, void *);
extern "C" void CStackFrame_Destructor(void *, int);
void LoadCoinFromBrx(COIN *coin, void *bis)
{
    char frame[0x10];
    int align = 0x10;
    CStackFrame_Construct(frame);
    ALLOCREQ req;
    ALLOCREQ *preq = &req;
    req.cb = 0x580;
    preq->cbAlign = align;
    coin->aloot = (COINLOOTDEF *)PvAllocStackImpl__Fi(preq);
    LoadDprizeFromBrx(coin, bis);
    func_001C7A08(coin);
    req.cb = coin->cloot * 0x2C;
    preq->cbAlign = align;
    coin->aloot = (COINLOOTDEF *)PvAllocSwCopyImpl__FiPv(preq, coin->aloot);
    CStackFrame_Destructor(frame, 2);
}
