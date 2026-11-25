#include "sly2.h"
#include "jt.h"
#include "phys.h"

union VecQw { QW q; float f[4]; };

/* the jump state's fields inside the JMP InitJt starts at 0x2C0 (SetJmpState takes its address), seen from the player */
struct JTJUMPVIEW {
    u8 unknown_0x0[0x2E8];
    int field_0x2E8;
    int field_0x2EC;
    u8 unknown_0x2F0[4];
    float duration;
    u8 unknown_0x2F8[8];
    int state;
    u8 unknown_0x304[0x5C];
    VecQw velocity;
};

extern "C" {
QW PosLoWorld(void *);
QW FCalculateMuzzleVelocity__FP6VECTORT0fT0P2SO(QW, QW, float, QW);
void SetJmpState(void *, int, int, int);
}

extern "C" void func_00141968(float gravity, float duration, JT *pjt, QW target)
{
    struct { VecQw posFrom; VecQw vel; } local;
    JTJUMPVIEW *view = (JTJUMPVIEW *)pjt;
    local.posFrom.q = PosLoWorld(pjt);
    local.posFrom.f[2] = local.posFrom.f[2] + pjt->vecLocal.z;
    local.vel.q = FCalculateMuzzleVelocity__FP6VECTORT0fT0P2SO(local.posFrom.q, target, gravity, pjt->pphys->dvGravity);
    pjt->Slot35(local.vel.q);
    if (pjt->zapState == -1) {
        SetJmpState(pjt->PvJmp(), 8, 0, 0);
        view->state = 3;
        view->velocity.q = local.vel.q;
        view->velocity.f[2] = 0.0f;
        view->duration = duration;
        if (duration == view->velocity.f[2]) {
            view->field_0x2E8 = 0;
            view->field_0x2EC = 0;
        }
    }
}
