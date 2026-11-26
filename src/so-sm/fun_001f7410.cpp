#include "geom.h"
#include "sly2.h"
struct HALF { GEOM *ppart; u8 unknown_0x4[4]; void *pso; struct LO *plo; QW pos; QW unk20; QW vel; };
struct MQ { HALF half[2]; u8 unknown_0x80[0xAC - 0x80]; MQ *pnext; };
#include "so.h"
#include "oxa.h"
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
    for (MQ *contact = pso->poxa->pcontact; contact != 0; contact = contact->pnext) {
        int second = contact->half[0].pso != pso;
        HALF *self = &contact->half[second];
        if (self->ppart->grftak == 0) continue;
        HALF *other = &contact->half[1 - second];
        LO *target = PaloFindWkrAbsorber(other->plo, self->ppart->grftak);
        if (target == 0) continue;
        WKR wkr;
        memset(&wkr, 0, sizeof(WKR));
        wkr.psoSource = pso;
        wkr.ppartSource = self->ppart;
        wkr.ploTarget = target;
        wkr.grftak = self->ppart->grftak;
        wkr.damage = self->ppart->ashGrf[2];
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
