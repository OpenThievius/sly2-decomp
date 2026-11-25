#include "sly2.h"
#include "emitter.h"
int memcmp(const void *, const void *, unsigned int);
#include "alloc.h"
extern "C" {
void PostLoLoad(EMITTER *);
void *PloFindSwObject_thunk(void *, int, int, void *);
void func_002590F0(EMITTER *, int);
void *PvAllocSwCopyImpl__FiPv(ALLOCREQ *, void *);
extern char B_003DD490[];
extern char D_002CE4B8[];
}
void PostSuvLoad(EMITTER *emitter)
{
    void *apv[5];
    PostLoLoad(emitter);
    int oidReference = emitter->pemitb->oidReference;
    int oidCurve = -1;
    if (emitter->pemitb->emitok == 2)
        oidCurve = emitter->pemitb->field_0x30;
    memset(apv, 0, 0x14);
    if (oidReference != -1)
        apv[0] = PloFindSwObject_thunk(B_003DD490, 4, oidReference, emitter);
    if (oidCurve != -1) {
        apv[1] = PloFindSwObject_thunk(B_003DD490, 4, oidCurve, emitter);
        apv[0] = 0;
    }
    EMITB *emitb = emitter->pemitb;
    int emitpk = emitb->emitpk;
    if (emitpk != 0) {
        if (emitpk == 1) {
            int oidA = emitb->params.oidA;
            int oidB = emitb->params.oidB;
            int oidC = emitb->params.oidC;
            if (oidA != -1)
                apv[2] = PloFindSwObject_thunk(B_003DD490, 4, oidA, emitter);
            if (oidB != -1)
                apv[3] = PloFindSwObject_thunk(B_003DD490, 4, oidB, emitter);
            if (oidC != -1)
                apv[4] = PloFindSwObject_thunk(B_003DD490, 4, oidC, emitter);
        }
    } else {
        int oid = emitb->params.oidSpline;
        if (oid != -1)
            apv[2] = PloFindSwObject_thunk(B_003DD490, 4, oid, emitter);
    }
    if (emitter->pemitb->pinfo == 0)
        emitter->pemitb->pinfo = (EMITBINFO *)D_002CE4B8;
    if (memcmp(emitter->pemitb->pinfo, apv, 0x14) != 0) {
        func_002590F0(emitter, 1);
        ALLOCREQ req;
        ALLOCREQ *preq = &req;
        preq->cb = 0x14;
        preq->cbAlign = 0x10;
        emitter->pemitb->pinfo = (EMITBINFO *)PvAllocSwCopyImpl__FiPv(preq, apv);
    }
}
