#include "sly2.h"
#include "so.h"
#include "xf.h"
/* Points *ref, an XF of src's transforms (or of its parent's), at the XF of the same index in so's (or so's parent's), and
   re-points that XF's ptMin and ptMax at its own tMin and tMax when they pointed at the source's. */
extern "C" void func_001F4CA0(SO *so, SO *src, int *ref)
{
    int old = *ref;
    if (old == 0) return;
    XF *nw = 0;
    int idx = (old - (sptr)src->axf) >> 8;
    if (idx >= 0 && idx < so->cxf) {
        nw = so->axf + idx;
    } else {
        SO *srcparent = src->psoParent;
        idx = (old - (sptr)srcparent->axf) >> 8;
        if (idx >= 0 && idx < srcparent->cxf)
            nw = so->psoParent->axf + idx;
    }
    if ((int)nw->ptMin == old + 0x80)
        nw->ptMin = &nw->tMin;
    if ((int)nw->ptMax == old + 0x84)
        nw->ptMin = &nw->tMax;
    *ref = (sptr)nw;
}
