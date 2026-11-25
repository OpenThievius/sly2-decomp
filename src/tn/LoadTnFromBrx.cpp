#include "alloc.h"
#include "tn.h"
#include "crv.h"
struct PLOARRAY {
    void *field_0x0;
    s32 cploMax;
    s32 cplo;
    LO **aplo;
};
extern "C" {
void LoadXfmBaseFromBrx(void *, void *);
void CBinaryInputStream_ReadGeom(void *, void *);
void CBinaryInputStream_ReadBspc(void *, void *, void *);
void *CStackFrame_Construct(void *);
void CStackFrame_Destructor(void *, int);
void *PvAllocStackImpl__Fi(ALLOCREQ *);
void *PvAllocSwCopyImpl__FiPv(ALLOCREQ *, void *);
void func_00221818(void *, int);
void func_00221940(void *);
void LoadOptionsFromBrx__FPvP18CBinaryInputStream(void *, void *);
void InitPloarray(PLOARRAY *);
void LoadPloarrayFromBrx(void *, void *, PLOARRAY *);
}

extern "C" void LoadTnFromBrx(TN *tn, void *bis)
{
    char frame[0x10];
    PLOARRAY pa;
    int align = 0x10;
    u8 *geom = tn->geom;
    LoadXfmBaseFromBrx(tn, bis);
    CBinaryInputStream_ReadGeom(bis, geom);
    CBinaryInputStream_ReadBspc(bis, geom, tn->bspc);
    CStackFrame_Construct(frame);
    ALLOCREQ *req = (ALLOCREQ *)&pa;
    req->cb = 0x240;
    req->cbAlign = align;
    tn->pstep = PvAllocStackImpl__Fi(req);
    func_00221818(tn, 0x30);
    LoadOptionsFromBrx__FPvP18CBinaryInputStream(tn, bis);
    func_00221940(tn);
    req->cb = tn->cstep * 0x90;
    req->cbAlign = align;
    void *world = PvAllocSwCopyImpl__FiPv(req, tn->pstep);
    tn->fStepsFixed = 1;
    tn->pstep = world;
    tn->pstepCurrent = world;
    InitPloarray(&pa);
    LoadPloarrayFromBrx(tn, bis, &pa);
    if (pa.cplo != 0) {
      if (pa.cplo == 1) {
        CRV *curve = (CRV *)*pa.aplo;
        tn->pcrv = curve;
        curve->grfo |= 0x200000000000000UL;
    } }
    if (tn->pcrv == 0)
        tn->flags &= ~2;
    CStackFrame_Destructor(frame, 2);
}
