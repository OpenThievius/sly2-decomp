#include "sly2.h"
#include "ps2inline.h"
#include "vu0inline.h"
struct VEC3F { float x, y, z, w; };
extern "C" {
s32 func_001EEF98(char *);
float SWrapCrv(float, char *);
void FindCrvClosestPointFromS(char *, VEC3F, float, void *, void *, VEC3F *, void *, float *);
VEC3F PosLoWorld(char *);
int func_0017CE30(char *);
void func_0017CD00(char *, int);
float atan2f(float, float);
void func_00209818(float);
void SetAsegaSpeed(char *, float);
extern float D_FLT_002BE74C;
}

extern "C" void PresetPuffcAccel__FP5PUFFCf(char *pgoal)
{
    func_001EEF98(pgoal);
    float *pStepDistance = &D_FLT_002BE74C;
    u32 negativeOneBits = 0xBF800000u;
    int nStatePrevious = *(int *)(pgoal + 0x30);
    do {
        if (nStatePrevious == 0) {
            char *pguard = *(char **)(pgoal + 0x10);
            char *pcrv = *(char **)(pguard + 0xF84);
            int fForward = (*(float *)(pguard + 0xF88)) < *(float *)(pgoal + 0x3C);
            *(int *)(pguard + 0xF8C) = fForward;
            VEC3F posGuard = PosLoWorld(*(char **)(pgoal + 0x10));
            float sAhead = fForward ? (*(float *)(pguard + 0xF88)) + *pStepDistance : (*(float *)(pguard + 0xF88)) - *pStepDistance;
            float sSearch = SWrapCrv(sAhead, pcrv);
            VEC3F vecTangent;
            float sClosest;
            FindCrvClosestPointFromS(pcrv, posGuard, sSearch, 0, 0, &vecTangent, 0, &sClosest);
            *(float *)(*(char **)(pgoal + 0x10) + 0xF88) = sClosest;
            if (func_0017CE30(pgoal) != 0) {
                func_0017CD00(pgoal, 1);
            } else {
                if (*(int *)(*(char **)(pgoal + 0x10) + 0xF8C) == 0) {
                    *(QW *)&vecTangent = VectorScaleX(*(QW *)&vecTangent, VectorFromWord(negativeOneBits));
                }
                float radHeading = atan2f(vecTangent.y, vecTangent.x);
                func_00209818(radHeading);
                char *precordAnim = *(char **)(*(char **)(pgoal + 0x18) + 0x40);
                SetAsegaSpeed(*(char **)(precordAnim + 8), *(float *)(pgoal + 0x38));
            }
        }
        nStatePrevious = *(int *)(pgoal + 0x30);
    } while (nStatePrevious != *(int *)(pgoal + 0x30));
}
