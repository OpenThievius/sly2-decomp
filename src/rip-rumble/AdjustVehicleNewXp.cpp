#include "sly2.h"
#include "so.h"
#include "laser.h"
#include "ps2inline.h"
#include "vu0inline.h"

union VU_SCALE {
    QW q;
    VECTOR v;
};
struct UL {
    u64 v;
} __attribute__((packed));

extern "C" char B_003DD490[];
extern "C" const UL RO_002A7840;
void func_001F4FB0(SO *, MQ *, int);
int FIsBasicDerivedFrom(void *, int);
void QueueSwCallbackOnce(void *, SO *, u64, int);

void AdjustVehicleNewXp(SO *pvehicle, MQ *pcontact, int side)
{
    func_001F4FB0(pvehicle, pcontact, side);
    void *plo = pcontact->aside[1 - side].plo;
    QW normal;
    if (side == 0) {
        normal = pcontact->normal;
    } else {
        VU_SCALE scale;
        scale.q = VectorFromFloat(-1.0f);
        normal = VectorScaleX(pcontact->normal, scale.q);
    }
    if (FIsBasicDerivedFrom(plo, 0x4D) != 0 || LaneZInGeneralRegister(normal) < 0.7f) {
        pcontact->friction = 0.0f;
        pcontact->bounce = 0.1f;
    } else {
        pcontact->friction = 0.5f;
        pcontact->bounce = 0.1f;
    }
    if (FIsBasicDerivedFrom(plo, 0x6C)) {
        QueueSwCallbackOnce(B_003DD490, pvehicle, RO_002A7840.v, (sptr)plo);
    }
}
