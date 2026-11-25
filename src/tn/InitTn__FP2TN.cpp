#include "sly2.h"
#include "tn.h"
#include "sw.h"
struct B8 { char b[8]; };
extern "C" {
extern const QW D_002C41C0;
extern const B8 D_002C41D0;
void InitXfm(void *);
void func_001A6CA8(void *, int);
void InitTn__FP2TN(TN *ptn)
{
    InitXfm(ptn);
    const QW *pq = &D_002C41C0;
    ptn->field_0x178 = 2.0f;
    ptn->field_0x170 = 2.0f;
    ptn->field_0x17C = 1.0f;
    ptn->field_0x174 = 1.0f;
    ptn->field_0x180 = -1;
    ptn->field_0x1A0 = *pq;
    *(B8 *)ptn->field_0x1B0 = D_002C41D0;
    ptn->tnsOverride = -1;
    ptn->flags = 7;
    func_001A6CA8(ptn, 1);
    if (!(ptn->grfSw & 1))
        ptn->pgrfentry->grf |= 2;
    else
        ptn->grfSw |= 2;
}
}
