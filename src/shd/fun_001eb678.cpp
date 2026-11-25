#include "sly2.h"
#include "alloc.h"
#include "shd.h"
#include "shdframes.h"
extern "C" void *PvAllocSwClearImpl__Fi(ALLOCREQ *);
extern "C" s64 func_001EA6C8(TEX *, int, int);

void func_001EB678(SHD *pshd, SHDFRAMES *pframes)
{
    ALLOCREQ allocreq;
    pframes->oid = pshd->oid;
    pframes->field_0x6 = pshd->field_0x6;
    pframes->grf = pshd->grf;
    pframes->rgba8 = pshd->rgba8;
    TEX *atex = pshd->atex;
    int cframe = atex->cbmp;
    allocreq.cb = cframe * 8;
    allocreq.cbAlign = 0x10;
    pframes->cframe = cframe;
    pframes->aframe = (s64 *)PvAllocSwClearImpl__Fi(&allocreq);
    for (int iframe = 0; iframe < pframes->cframe; iframe++)
    {
        s64 *slot = (s64 *)(iframe * 8 + (sptr)pframes->aframe);
        *slot = func_001EA6C8(atex, iframe, 0);
    }
}
