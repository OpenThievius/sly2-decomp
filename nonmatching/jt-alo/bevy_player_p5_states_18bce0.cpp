#include "sly2.h"
#include "ps2inline.h"
#include "vu0inline.h"
union VU_SCALE { QW q; VECTOR v; };
extern "C" {
void UpdateJt();
void bevy_player_input_from_pad_cm(char *);
void SetStepRadTarget(char *, float);
void SetRunBlendU(char *, float);
void UpdateRunBlendFootsteps(char *);
void SolvePlainBlendWeights(char *, char *, int);
void UpdateJtStand__FP2JT(char *);
void UpdateJtHangPose(char *);
void UpdateJtSurfaceWalk(char *);
void UpdateJtRide(char *);
void RebuildJtXmg__FP2JTP3ALOfT1P6ACTADJP3XMG(char *, int, int, int, char *, float);
int FMatchJtXmg(char *, char *, int);
void EnsureAloSfx__FP3ALO(char *);
int FIsBasicDerivedFrom(char *, int);
void FindCrvClosestPointFromS(char *, QW, int, VECTOR *, int, int, int, float);
QW PosLoWorld(char *);
void FindClosestPointBetweenLineSegments__FP6VECTORN40PfT0(QW, QW, QW, QW, VECTOR *, float *, VECTOR *);
void SetJtState(char *, int, int);
void UpdateJtBalance(char *);
extern int D_002BF3D4;
extern int D_002BF3D8;
extern float D_FLT_002BF3DC;
}
void bevy_player_p5_states_18bce0(char *jt)
{
    VU_SCALE scale;
    VECTOR points[3];
    VECTOR other;
    float tDistance;
    UpdateJt();
    if (((int)(*(unsigned long *)(jt + 0x28) >> 0x3C)) & 1) {
        if (*(int *)(jt + 0x150) != 0)
            bevy_player_input_from_pad_cm(jt);
        switch (*(unsigned int *)(jt + 0x18C8)) {
        case 1:
            SetStepRadTarget(jt, *(float *)(*(char **)(jt + 0x150) + 0x18));
            SetRunBlendU(jt + 0x1320, 1.0f);
            UpdateRunBlendFootsteps(jt + 0x1320);
            scale.q = VectorFromWord(D_002BF3D4);
            *(QW *)(jt + 0x190) = VectorScaleX(*(QW *)(jt + 0x190), scale.q);
            break;
        case 5:
            if (*(int *)(jt + 0x18D0) == 5) {
                SolvePlainBlendWeights(jt, jt + 0x13D0, *(int *)(jt + 0x14D0));
                scale.q = VectorFromWord(D_002BF3D8);
                *(QW *)(jt + 0x190) = VectorScaleX(*(QW *)(jt + 0x190), scale.q);
                *(float *)(jt + 0x180) = 1.0f;
            }
            break;
        case 10:
            SolvePlainBlendWeights(jt, jt + 0x1AC0, *(int *)(jt + 0x1BC0));
            break;
        case 0:
            UpdateJtStand__FP2JT(jt);
            break;
        case 3:
            UpdateJtHangPose(jt);
            break;
        case 12:
            UpdateRunBlendFootsteps(jt + 0x1C30);
            break;
        case 21:
            UpdateJtSurfaceWalk(jt);
            break;
        case 22:
            UpdateJtRide(jt);
            break;
        case 24:
            if (*(int *)(jt + 0x19F0) != 0) {
                char *first = jt + 0x1520;
                char *second = jt + 0x1620;
                RebuildJtXmg__FP2JTP3ALOfT1P6ACTADJP3XMG(jt, *(int *)(jt + 0x19D8), *(int *)(jt + 0x19E0), *(int *)(jt + 0x19F0), first, D_FLT_002BF3DC);
                RebuildJtXmg__FP2JTP3ALOfT1P6ACTADJP3XMG(jt, *(int *)(jt + 0x19D4), *(int *)(jt + 0x19DC), *(int *)(jt + 0x19F4), second, D_FLT_002BF3DC);
                FMatchJtXmg(jt, first, *(int *)(jt + 0x19F0));
                FMatchJtXmg(jt, second, *(int *)(jt + 0x19F4));
            }
            break;
        }
        EnsureAloSfx__FP3ALO(jt);
        if (*(int *)(jt + 0x18D8) == 0) {
            char *target = *(char **)(jt + 0x1854);
            bool ready = false;
            if (FIsBasicDerivedFrom(target, 0xB) != 0) {
                for (int index = 0; index < 3; index++)
                    FindCrvClosestPointFromS(target, ((QW *)(jt + 0x1890))[index], 0, &points[index], 0, 0, 0, *(float *)(jt + 0x1858));
                ready = true;
            } else if (FIsBasicDerivedFrom(*(char **)(jt + 0x1854), 0x13) != 0) {
                QW position = PosLoWorld(*(char **)(jt + 0x1854));
                *(QW *)&points[0] = position;
                *(QW *)&points[2] = position;
                *(QW *)&points[1] = position;
                ready = true;
            }
            if (ready) {
                for (int index = 1; index < *(int *)(jt + 0x1880); index++) {
                    FindClosestPointBetweenLineSegments__FP6VECTORN40PfT0(((QW *)(jt + 0x1890))[index - 1], ((QW *)(jt + 0x1890))[index], *(QW *)&points[index - 1], *(QW *)&points[index], &scale.v, &tDistance, &other);
                    if (tDistance < *(float *)(jt + 0x19AC)) {
                        if (FIsBasicDerivedFrom(*(char **)(jt + 0x1854), 0x13) == 0) {
                            *(char **)(jt + 0xF5C) = *(char **)(jt + 0x1854);
                            *(float *)(jt + 0xF60) = *(float *)(jt + 0x1858);
                            SetJtState(jt, 8, -1);
                        } else {
                            char *ride = *(char **)(jt + 0x1854);
                            *(char **)(jt + 0x18C4) = ride;
                            if (*(int *)(ride + 0x124) != 3)
                                SetJtState(jt, 3, 1);
                            else
                                SetJtState(jt, 0x16, -1);
                        }
                        break;
                    }
                }
            }
        }
        UpdateJtBalance(jt);
    }
}
