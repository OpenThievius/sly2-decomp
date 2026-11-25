#include "sly2.h"
#include "alloc.h"
#include "laser.h"
extern "C" void * CStackFrame_Construct(void *);
extern "C" void *PvAllocStackClearImpl__Fi(ALLOCREQ *);
extern "C" void CSo_LoadFromBrx(LASER *, void *);
extern "C" void *PvAllocSwCopyImpl__FiPv(ALLOCREQ *, void *);
extern "C" void CStackFrame_Destructor(void *, int);
extern "C" void LoadLaserFromBrx(LASER *laser, void *bis)
{
    char frame[0x10];
    int align = 0x10;
    CStackFrame_Construct(frame);
    ALLOCREQ req;
    ALLOCREQ *preq = &req;
    req.cb = 0x5400;
    preq->cbAlign = align;
    laser->abeam = (BEAM *)PvAllocStackClearImpl__Fi(preq);
    CSo_LoadFromBrx(laser, bis);
    req.cb = laser->cbeam * sizeof(BEAM);
    preq->cbAlign = align;
    laser->abeam = (BEAM *)PvAllocSwCopyImpl__FiPv(preq, laser->abeam);
    CStackFrame_Destructor(frame, 2);
}
