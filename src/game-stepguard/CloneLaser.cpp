#include "alloc.h"
#include "laser.h"
extern "C" void CSo_Clone(LASER *);
extern "C" void *PvAllocSwCopyImpl__FiPv(ALLOCREQ *, void *);
extern "C" void CloneLaser(LASER *laser)
{
    CSo_Clone(laser);
    BEAM *src = laser->abeam;
    ALLOCREQ req;
    req.cb = laser->cbeam * sizeof(BEAM);
    req.cbAlign = 0x10;
    laser->abeam = (BEAM *)PvAllocSwCopyImpl__FiPv(&req, src);
}
