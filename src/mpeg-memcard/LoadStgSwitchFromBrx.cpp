#include "sly2.h"
#include "alloc.h"
#include "stgswitch.h"
extern "C" void *CStackFrame_Construct(void *);
extern "C" void *PvAllocStackImpl__Fi(ALLOCREQ *);
extern "C" void *PvAllocStackClearImpl__Fi(ALLOCREQ *);
extern "C" void *PvAllocSwCopyImpl__FiPv(ALLOCREQ *, void *);
extern "C" void CSo_LoadFromBrx(STGSWITCH *, void *);
extern "C" void CStackFrame_Destructor(void *, int);
static inline ALLOCREQ *Aligned(ALLOCREQ *request)
{
    request->cbAlign = 0x10;
    return request;
}
void LoadStgSwitchFromBrx(STGSWITCH *pstgsw, void *pbis)
{
    char frame[0x10];
    CStackFrame_Construct(frame);
    ALLOCREQ req;
    req.cb = 0x40;
    pstgsw->aclass = (STGCLASS *)PvAllocStackImpl__Fi(Aligned(&req));
    req.cb = 0x200;
    pstgsw->anode = (STGNODE *)((char *)PvAllocStackClearImpl__Fi(Aligned(&req)) + 0x10);
    CSo_LoadFromBrx(pstgsw, pbis);
    STGCLASS *table = pstgsw->aclass;
    pstgsw->istage = 0;
    req.cb = pstgsw->cclass * 8;
    pstgsw->aclass = (STGCLASS *)PvAllocSwCopyImpl__FiPv(Aligned(&req), table);
    if (pstgsw->cstage != 0) {
        req.cbAlign = 0x10;
        req.cb = pstgsw->cstage * 0x10 + 0x10;
        pstgsw->anode = (STGNODE *)((char *)PvAllocSwCopyImpl__FiPv(&req, (char *)pstgsw->anode - 0x10) + 0x10);
        for (int iGroup = -1; iGroup < pstgsw->cstage; iGroup++) {
            STGNODE *pgroup = pstgsw->anode + iGroup;
            STGENT *entries = pgroup->aent;
            req.cb = pgroup->count * 8;
            pgroup->aent = (STGENT *)PvAllocSwCopyImpl__FiPv(Aligned(&req), entries);
            for (int iEntry = 0; iEntry < pgroup->count; iEntry++) {
                STGENT *pentry = pgroup->aent + iEntry;
                if (pentry->kind == 0xC) {
                    void *value = pentry->pv;
                    req.cb = 8;
                    pentry->pv = PvAllocSwCopyImpl__FiPv(Aligned(&req), value);
                }
            }
        }
    } else {
        pstgsw->anode = 0;
    }
    CStackFrame_Destructor(frame, 2);
}
