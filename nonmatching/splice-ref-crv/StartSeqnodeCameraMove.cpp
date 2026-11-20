#include "sly2.h"
#include "ps2inline.h"
struct CAMPOSE_1E57A0 { QW position; QW rotation; float speed; };
struct SEQCAM_1E57A0 {
    char pad0[0x80]; float endTime; CAMPOSE_1E57A0 *poses[2]; float duration; int field90; int field94; SEQCAM_1E57A0 *self; int field9c;
};
struct CAMSRC_1E57A0 { char pad0[0x10]; CAMPOSE_1E57A0 pose; float duration; int field44; };
extern "C" {
float RadNormalize__Ff(float);
int FActiveCplcy(void *);
int FFloatsNear__Ffff(float, float, float);
QW DecomposeRotateMatrixEuler(void *);
void RevokeCmPolicy__FP2CMi3CPPP5CPLCYP2SOPv(void *, int, int, void *, void *, void *);
void SetCmPolicy__FP2CM3CPPP5CPLCYP2SOPv(void *, int, void *, int, void *);
}
extern QW g_2a2dd0;
extern float g_2dded0;
extern MATRIX4 g_2ddfa0;
extern VECTOR B_002DDF40[];
extern char B_002DE440[];
static inline int Near(float a, float b) { return FFloatsNear__Ffff(a, b, 0.0001f); }
static inline int Near3(QW p, QW q)
{
    int ok = 0;
    if (Near(LaneX(p), LaneX(q)) && Near(LaneYInGeneralRegister(p), LaneYInGeneralRegister(q))) {
        if (Near(LaneZInGeneralRegister(p), LaneZInGeneralRegister(q))) {
            ok = 1;
        }
    }
    return ok;
}
extern "C" void StartSeqnodeCameraMove(SEQCAM_1E57A0 *seq, CAMSRC_1E57A0 *from, CAMSRC_1E57A0 *to, float time)
{
    if (from->duration == 0.0f) {
        seq->endTime = 3.4028235e38f;
    } else {
        *(int *)((char *)to + 4) = 0;
        seq->endTime = g_2dded0 + time;
    }
    seq->poses[0] = &from->pose;
    seq->poses[1] = &to->pose;
    seq->duration = time;
    seq->field90 = 1;
    float *fromRot = (float *)&from->pose.rotation;
    float *toRot = (float *)&to->pose.rotation;
    int count = 2;
    seq->field9c = 1;
    seq->field94 = from->field44;
    seq->self = seq;
    do {
        count--;
        float delta = RadNormalize__Ff(*toRot - *fromRot);
        float base = *fromRot++;
        *toRot++ = base + delta;
    } while (count >= 0);
    CAMPOSE_1E57A0 **cursor = seq->poses;
    for (unsigned int index = 0; index < 2; index++) {
        CAMPOSE_1E57A0 *pose = *cursor++;
        if (Near3(g_2a2dd0, pose->position)) {
            pose->position = g_2ddfa0.row[3];
        }
        if (Near3(g_2a2dd0, pose->rotation)) {
            pose->rotation = DecomposeRotateMatrixEuler(&g_2ddfa0);
        }
        if (pose->speed == 0.0f) {
            pose->speed = B_002DDF40[2].x;
        }
    }
    if (seq->duration == 0.0f) {
        seq->duration = 3.4028235e38f;
    }
    if (FActiveCplcy(B_002DE440)) {
        RevokeCmPolicy__FP2CMi3CPPP5CPLCYP2SOPv(B_002DE440 - 0x500, 2, 0xA, B_002DE440, 0, *(void **)(B_002DE440 - 0x500 + 0x510));
    }
    SetCmPolicy__FP2CM3CPPP5CPLCYP2SOPv(B_002DE440 - 0x500, 0xA, B_002DE440, 0, seq->poses);
}
