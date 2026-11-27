#include "geom.h"
#include "sly2.h"
#include "so.h"
#include "oxa.h"
#include "xp.h"
#include "wkr.h"
struct SW;
extern "C" {
extern char B_003DD490;
LO *PaloFindWkrAbsorber(LO *, int);
SO *PaloAbsorbWkr(WKR *);
void FreeSwMqList__FP2SWP2MQ(void *, void *);
}
void func_001F7410(SO *pso)
{
    for (XP *contact = pso->poxa->pcontact; contact != 0; contact = contact->pxpNext) {
        int second = contact->axpd[0].psoRoot != pso;
        XPD *self = &contact->axpd[second];
        if (self->pgeom->grftak == 0) continue;
        XPD *other = &contact->axpd[1 - second];
        LO *target = PaloFindWkrAbsorber(other->pso, self->pgeom->grftak);
        if (target == 0) continue;
        WKR wkr;
        memset(&wkr, 0, sizeof(WKR));
        wkr.psoSource = pso;
        wkr.ppartSource = self->pgeom;
        wkr.ploTarget = target;
        wkr.grftak = self->pgeom->grftak;
        wkr.damage = self->pgeom->ashGrf[2];
        wkr.pos = other->pos;
        wkr.vel = self->vel;
        PaloAbsorbWkr(&wkr);
        if (pso->poxa == 0) return;
    }
    if (pso->poxa != 0) {
        FreeSwMqList__FP2SWP2MQ(&B_003DD490, pso->poxa->pcontact);
        pso->poxa->pcontact = 0;
    }
}
