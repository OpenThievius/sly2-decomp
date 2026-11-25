#include "tn.h"
/* one camera step of a tunnel, 0x90 bytes: the first word is the step's id */
struct Step { s32 cid; u8 unknown_0x4[0xC]; QW unknown_0x10[8]; };
extern "C" void func_00221940(TN *);
extern Step D_002C4120;

extern "C" void func_00221818(TN *tn, int cid)
{
    func_00221940(tn);
    if (tn->cstep < 4) {
        for (int i = 0; i < tn->cstep; i++) {
            if (((Step *)tn->pstep)[i].cid == cid) {
                tn->pstepCurrent = &((Step *)tn->pstep)[i];
                return;
            }
        }
        Step *steps = (Step *)tn->pstep;
        if (tn->fStepsFixed != 0) {
            tn->pstepCurrent = steps;
            return;
        }
        Step *added = &steps[tn->cstep++];
        tn->pstepCurrent = added;
        if (tn->cstep >= 2)
            *added = steps[tn->cstep - 2];
        else
            *added = D_002C4120;
        ((Step *)tn->pstepCurrent)->cid = cid;
    }
}
