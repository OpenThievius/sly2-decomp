#include "alloc.h"
#include "jsg.h"
extern "C" void CLo_Clone(JSG *);
extern "C" void *PvAllocSwCopyImpl__FiPv(ALLOCREQ *, void *);
extern "C" void CSeq_Clone(JSG *seq)
{
    CLo_Clone(seq);
    if (seq->fOwnsAjsge != 0) {
        void *src = (void *)seq->ajsge;
        ALLOCREQ req;
        req.cb = seq->cjsgeMax * 0x50;
        req.cbAlign = 0x10;
        seq->ajsge = (sptr)PvAllocSwCopyImpl__FiPv(&req, src);
    }
}
