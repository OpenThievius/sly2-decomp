#include "bis.h"
#include "alloc.h"
#include "crv.h"
extern "C" {
void CBinaryInputStream_Read_thunk(CBinaryInputStream *, int, void *);
void LoadOptionsFromBrx__FPvP18CBinaryInputStream(void *, CBinaryInputStream *);
void LoadXfmBaseFromBrx(CRV *, CBinaryInputStream *);
void MeasureCrv(CRV *);
void *PvAllocSwImpl__Fi(ALLOCREQ *);
}
extern "C" void LoadCrvFromBrx(CRV *pcrv, CBinaryInputStream *pbis)
{
    ALLOCREQ req;
    int index;
    LoadXfmBaseFromBrx(pcrv, pbis);
    pcrv->crvk = pbis->S8Read();
    pcrv->closed = pbis->S8Read();
    pcrv->ccv = pbis->U16Read();
    req.cb = pcrv->ccv * 4;
    req.cbAlign = 0x10;
    pcrv->au = (f32 *)PvAllocSwImpl__Fi(&req);
    req.cb = pcrv->ccv * 4;
    req.cbAlign = 0x10;
    pcrv->as = (f32 *)PvAllocSwImpl__Fi(&req);
    req.cb = pcrv->ccv * 0x10;
    req.cbAlign = 0x10;
    pcrv->apos = (QW *)PvAllocSwImpl__Fi(&req);
    CBinaryInputStream_Read_thunk(pbis, pcrv->ccv * 4, pcrv->au);
    for (index = 0; index < pcrv->ccv; index++)
        pbis->ReadVector((VECTOR *)&pcrv->apos[index]);
    if (pcrv->crvk != 0) {
        req.cb = pcrv->ccv * 0x10;
        req.cbAlign = 0x10;
        pcrv->field_0x140 = (QW *)PvAllocSwImpl__Fi(&req);
        req.cb = pcrv->ccv * 0x10;
        req.cbAlign = 0x10;
        pcrv->field_0x144 = (QW *)PvAllocSwImpl__Fi(&req);
        for (index = 0; index < pcrv->ccv; index++)
            pbis->ReadVector((VECTOR *)&pcrv->field_0x140[index]);
        for (index = 0; index < pcrv->ccv; index++)
            pbis->ReadVector((VECTOR *)&pcrv->field_0x144[index]);
    }
    LoadOptionsFromBrx__FPvP18CBinaryInputStream(pcrv, pbis);
    MeasureCrv(pcrv);
}
