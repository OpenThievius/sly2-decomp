#include "stgswitch.h"
#include "alloc.h"
extern "C" void *PvAllocStackImpl__Fi(ALLOCREQ *);

void InitStgSwitchPreStage(STGSWITCH *pswitch) {
    pswitch->istage = -1;
    STGNODE *base = pswitch->anode;
    base[-1].id = -1;
    STGNODE *stage = base - 1;
    stage->fForward = 1;
    if (stage->ents == 0) {
        ALLOCREQ req;
        req.cb = 0x200;
        req.cbAlign = 0x10;
        stage->ents = PvAllocStackImpl__Fi(&req);
    }
}
