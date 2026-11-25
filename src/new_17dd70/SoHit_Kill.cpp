#include "sohit.h"
#include "sly2.h"
struct SOHITKILLWKR { SOHIT *pso; u8 unknown_0x4[4]; void *victim; s32 kind; s32 dhp; u8 unknown_0x14[0xC]; QW pos; QW velocity; u8 unknown_0x40[0x20]; };
extern "C" QW PosLoWorld(void *);
extern "C" void PaloAbsorbWkr(SOHITKILLWKR *);
extern "C" void ExplodeExpl(void *);
extern "C" void SoHit_Kill(SOHIT *so, void *victim)
{
    if (victim != 0 && so->dhp != 0) {
        SOHITKILLWKR wkr;
        memset(&wkr, 0, sizeof(SOHITKILLWKR));
        wkr.victim = victim;
        wkr.pso = so;
        wkr.pos = PosLoWorld(so);
        wkr.velocity = so->GetVelocityVec();
        wkr.dhp = -so->dhp;
        wkr.kind = 0x100;
        PaloAbsorbWkr(&wkr);
    }
    if (so->pexpl != 0)
        ExplodeExpl(so->pexpl);
    so->Remove();
}
