#include "murray.h"
#include "ps2inline.h"
#include "vu0inline.h"
#include "sly2.h"
union VU_SCALE { QW q; VECTOR v; };
struct PJOYVIEW { char pad0[0x18]; float radTarget; float speed; };
struct OXAHOLDER { char pad0[0xEC]; void *poxa; };
extern "C" {
void BuildJtTargetList(void *, void *, int);
int FAsegaGone(int);
int FPoxaPairInteracts(void *, void *, void *);
void MoveMurrayAttack(void *);
void RecalcSwOxfFilterForObject(void *, void *);
void ReleaseAsegaHandle(void *);
float SetAsegaSpeed(void *, float);
void SetRunBlendU(void *, float);
void SetSmaMask(int, int);
void SetStepRadTarget(void *, float);
void UpdateAttachMotion(void *);
void UpdateJt();
void UpdateMurrayActive(void *);
void UpdateMurrayBinoc(void *);
void UpdateMurrayStandOn(void *);
void UpdateRunBlendFootsteps(void *);
void UpdateZapPost(void *);
void bevy_player_p18_gadget_glide_steer(void *);
void func_0012D108(int, QW);
int func_001430C8(void *);
void func_001B90B8(void *);
QW func_00204E38(void *, void *, float);
extern char B_003DD490;
extern QW D_002C08F0;
extern float D_FLT_002C08E4;
extern QW RO_002A2DE0;
extern float g_2dded0;
}

static inline void StoreNegatedVelocity(MURRAY *self, QW v)
{
    VU_SCALE scale;
    scale.q = VectorFromFloat(-1.0f);
    self->velGoal = VectorScaleX(v, scale.q);
}

extern "C" void UpdateMurray(MURRAY *self)
{
    UpdateJt();
    if (((self->grfo >> 0x3C) & 1) == 0)
        return;
    int hAsega = *(int *)((char *)self + 0x190C);
    if (hAsega != 0 && FAsegaGone(hAsega) != 0)
        ReleaseAsegaHandle((char *)self + 0x190C);
    BuildJtTargetList(&B_003DD490, self, 0xF8FA);
    UpdateMurrayBinoc(self);
    UpdateMurrayActive(self);
    switch (self->state) {
    case 0:
        SetSmaMask((int)self->field_0x1034, func_001430C8(self));
        break;
    case 1: {
        char *pblend = (char *)self + 0x1320;
        SetStepRadTarget(self, ((PJOYVIEW *)self->pjoy)->radTarget);
        SetRunBlendU(pblend, 1.0f);
        UpdateRunBlendFootsteps(pblend);
        break;
    }
    case 10: {
        char *pblend = (char *)self + 0x1540;
        SetStepRadTarget(self, ((PJOYVIEW *)self->pjoy)->radTarget);
        SetRunBlendU(pblend, ((PJOYVIEW *)self->pjoy)->speed);
        UpdateRunBlendFootsteps(pblend);
        break;
    }
    case 2:
        bevy_player_p18_gadget_glide_steer((char *)self + 0x2C0);
        break;
    case 13:
        UpdateAttachMotion((char *)self + 0x4C0);
        break;
    case 11:
        MoveMurrayAttack(self);
        break;
    case 12:
        func_001B90B8(self);
        break;
    case 17: {
        char *ptarget = (char *)self->field_0x1030;
        StoreNegatedVelocity(self, func_00204E38(self, ptarget, *(float *)(ptarget + 0x1C)));
        break;
    }
    case 18: {
        char *ptarget = (char *)self->field_0x1030;
        QW velocity = func_00204E38(self, ptarget, *(float *)(ptarget + 0x1C));
        VU_SCALE scale;
        scale.q = VectorFromFloat(-1.0f);
        self->velGoal = VectorScaleX(velocity, scale.q);
        SetAsegaSpeed(self->field_0x1030, ((PJOYVIEW *)self->pjoy)->speed);
        SetStepRadTarget(self, ((PJOYVIEW *)self->pjoy)->radTarget);
        break;
    }
    }
    UpdateMurrayStandOn(self);
    UpdateZapPost((char *)self + 0xDF0);
    if (self->psoDropped != 0 && self->field_0x1434 + 0.1f < g_2dded0) {
        void *poxaDropped = ((OXAHOLDER *)self->psoDropped)->poxa;
        if (poxaDropped == 0 || FPoxaPairInteracts(&B_003DD490, self->poxa, poxaDropped) == 0)
            self->psoDropped = 0;
        if (self->psoDropped == 0)
            RecalcSwOxfFilterForObject(&B_003DD490, self);
    }
    if (self->field_0x1ACC != 0) {
        if (g_2dded0 - self->field_0x1AC8 < D_FLT_002C08E4)
            func_0012D108(self->field_0x1ACC, D_002C08F0);
        else
            func_0012D108(self->field_0x1ACC, RO_002A2DE0);
    }
}
