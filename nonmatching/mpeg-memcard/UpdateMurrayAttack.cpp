// SPDX-License-Identifier: GPL-3.0-or-later
struct PAD {
    char unknown_0x0[0x1C];
    float stick;
};
struct MURRAY_ATTACK {
    char unknown_0x0[0x150];
    PAD *ppad;
    char unknown_0x154[0xEDC];
    void *pasega;
    char unknown_0x1034[0x7DC];
    int state;
    char unknown_0x1814[0x8];
    int fAttacking;
};
extern "C" {
int FAsegaGone(void *);
int FButtonPressedWithin(PAD *, int, float);
int FMurrayAttackCanChain(MURRAY_ATTACK *);
int FMurrayTryGrabGuard(MURRAY_ATTACK *);
void SetMurrayAttackState(MURRAY_ATTACK *, int);
void SetMurrayState(MURRAY_ATTACK *, int);
void EndMurrayAttack(MURRAY_ATTACK *);

void UpdateMurrayAttack(MURRAY_ATTACK *murray)
{
    int statePrevious;
    for (;;) {
        statePrevious = murray->state;
        if (murray->pasega == 0 || FAsegaGone(murray->pasega) != 0) {
            SetMurrayState(murray, 0);
        } else {
            switch (murray->state) {
            case 0:
            case 1: {
                    if (FMurrayAttackCanChain(murray) && FButtonPressedWithin(murray->ppad, 0x80, 0.25f)) {
                        SetMurrayAttackState(murray, murray->state == 0);
                    } else if ((!FMurrayAttackCanChain(murray) || !FMurrayTryGrabGuard(murray)) && murray->fAttacking != 0
                               && murray->ppad->stick > 0.0f) {
                        EndMurrayAttack(murray);
                    }
                break;
            }
            case 2:
            case 3: {
                    if (FMurrayAttackCanChain(murray) && FButtonPressedWithin(murray->ppad, 0x10, 0.25f)) {
                        SetMurrayAttackState(murray, murray->state == 2 ? 3 : 2);
                    } else if ((!FMurrayAttackCanChain(murray) || !FMurrayTryGrabGuard(murray)) && murray->fAttacking != 0
                               && murray->ppad->stick > 0.0f) {
                        EndMurrayAttack(murray);
                    }
                break;
            }
            }
        }
        if (murray->state == statePrevious || murray->state == -1)
            break;
    }
}
}
