#include "crv.h"
/* the curve's rope simulation (ConstructRopeSim): its mode, which SetCrvRopeMode sets */
struct ROPESIM {
    u8 unknown_0x0[0x4C];
    /* 0x4C */ s32 nMode;
};
/* the getter beside SetCrvRopeMode in the property table D_002B85E0: the rope's mode, -1 without a rope */
extern "C" int func_001E7FF0(CRV* arg0)
{
    int v0 = -1;
    ROPESIM* v1 = arg0->pattach;
    if (v1 != 0) {
        v0 = v1->nMode;
    }
    return v0;
}
