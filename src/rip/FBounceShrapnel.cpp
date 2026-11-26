#include "sly2.h"
#include "geom.h"
#include "so.h"
#include "oxa.h"
struct RIP;
extern "C" {
int FIsBasicDerivedFrom(void *, int);
void RemoveRip(RIP *);
int FBounceRip__FP3RIPP2SOP6VECTORT2(RIP *, GEOM *, QW, QW);
}
extern "C" int FBounceShrapnel(RIP *rip, GEOM *geom, QW pos, QW normal)
{
    void *owner = geom->pso->poxa->owner;
    if (FIsBasicDerivedFrom(owner, 0x32))
        return 0;
    if (FIsBasicDerivedFrom(owner, 0x59)) {
        RemoveRip(rip);
        return 1;
    }
    return FBounceRip__FP3RIPP2SOP6VECTORT2(rip, geom, pos, normal);
}
