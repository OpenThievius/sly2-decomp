#include "types.h"
#include "sly2.h"
#include "recon.h"
#include "vu0inline.h"
#include "ps2inline.h"

extern "C" QW PosLoWorld(void *);
extern "C" void FadeAloIn(LO *, float);
extern "C" void FadeAloOut(LO *, float);
extern QW B_002DDF40[];

void UpdateReconLinkFades(BINOCRECON *recon)
{
    for (int index = 0; index < recon->ctarget; index++) {
        RECON *target = recon->aptarget[index];
        if (target->plink != 0) {
            QW pos = PosLoWorld(target);
            QW offset = B_002DDF40[9];
            float distance = LaneX(SqrtX(SquaredLengthXy(VectorSub(pos, offset))));
            if (target->range < distance && ((target->plink->grfo >> 60) & 1) == 0)
                FadeAloIn(target->plink, 0.25f);
            else if (distance <= target->range && ((target->plink->grfo >> 60) & 1) == 1)
                FadeAloOut(target->plink, 0.25f);
        }
    }
}
