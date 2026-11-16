// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "ps2inline.h"
#include "vu0inline.h"
struct M4 { QW row[4]; };
struct Aloobj { char pad0[0xC]; struct VT *vtable; };
struct VT { char pad[0xF8]; short delta; short index; M4 *(*fn)(void *); };
struct Carry {
    void *pjt;
    void **ppasega;
    float weight0;
    char pad0[0x1C - 0xC];
    float weight1;
    char pad1[0x30 - 0x20];
    void *pasegbl;
    char pad2[0x38 - 0x34];
    char *pxfBase;
    char pad3[0x40 - 0x3C];
    M4 matBase;
    void *pactLook;
    Aloobj *pcrv;
    float sPath;
    Aloobj *ploTarget;
    int kind;
    char pad5[0xA4 - 0x94];
    int state;
};
union VU_QUAD { QW q; VECTOR v; };
struct Probe { Carry *pcarry; char pad[0xC]; QW posFlat; };
extern "C" {
QW PosLoWorld(void *);
void FindCrvClosestPointFromS(void *, QW, float, int, QW *, int, int, float *);
M4 InvertMatrix4Affine(M4 *);
M4 __ml__FRC7MATRIX4T0(const M4 &, const M4 &);
QW ConvertAloPos(void *, void *, QW);
float Carry_SDistStartCurves(void *, float);
float Carry_SDistEndCurves(void *, float);
void MinimizeRange__FPFPvf_fPvffffPfT6(float (*)(void *, float), void *, float *, float *, float, float, float, float);
void func_001CC1F8(Carry *, QW, float *, int, float);
void func_001CC168(Carry *, QW, float *, int, float);
M4 ConvertXfMat(void *, void *, QW *);
QW DecomposeRotateMatrixEuler(QW *);
void func_0012D108(void *, QW);
void SeekAsega(void *, int, float, float);
void ReblendAsegbl(void *);
void SetStepRadTargetDir(void *, QW);
void FixStepAngularVelocity__FP4STEP(void *);
}

extern "C" void func_001CC2E8(Carry *carry)
{
    if (carry->state == -1)
        return;
    VU_QUAD posTarget;
    QW rot[3];
    switch (carry->kind) {
    case 0: {
        Aloobj *crv = carry->pcrv;
        FindCrvClosestPointFromS(crv, PosLoWorld(carry->pjt), carry->sPath, 0, &posTarget.q, 0, 0, &carry->sPath);
        break;
    }
    case 1:
        posTarget.q = PosLoWorld(carry->ploTarget);
        break;
    case 2: {
        M4 mat;
        Aloobj *target = carry->ploTarget;
        mat = __ml__FRC7MATRIX4T0(*target->vtable->fn((char *)target + target->vtable->delta), InvertMatrix4Affine(&carry->matBase));
        posTarget.q = mat.row[3];
        QW *rows = mat.row;
        rot[0] = rows[0];
        rot[1] = rows[1];
        rot[2] = rows[2];
        break;
    }
    }
    Probe probe;
    VU_QUAD flat;
    probe.pcarry = carry;
    QW posLocal = ConvertAloPos(0, carry->pjt, posTarget.q);
    QW squared = SumXyInX(VectorMultiplyXy(posLocal, posLocal));
    flat.q = posLocal;
    QW root = SqrtX(squared);
    flat.v.y = 0.0f;
    *(u32 *)&flat.v.x = VectorWordX(root);
    probe.posFlat = ConvertAloPos(carry->pjt, 0, flat.q);
    float u, sdist, gblend;
    if (carry->kind == 2) {
        MinimizeRange__FPFPvf_fPvffffPfT6(Carry_SDistEndCurves, &probe, &u, &sdist, 0.5f, 0.1f, 0.0f, 1.0f);
        func_001CC1F8(carry, probe.posFlat, &gblend, 0, u);
        QW rot2[3];
        M4 inParent = ConvertXfMat(0, *(void **)(carry->pxfBase + 0xA0), rot);
        rot2[0] = inParent.row[0];
        rot2[1] = inParent.row[1];
        rot2[2] = inParent.row[2];
        func_0012D108(carry->pactLook, DecomposeRotateMatrixEuler(rot2));
    } else {
        MinimizeRange__FPFPvf_fPvffffPfT6(Carry_SDistStartCurves, &probe, &u, &sdist, 0.5f, 0.1f, 0.0f, 1.0f);
        func_001CC168(carry, probe.posFlat, &gblend, 0, u);
    }
    SeekAsega(*carry->ppasega, 0, u * *(float *)((char *)carry->pasegbl + 0x74), 0.0f);
    carry->weight1 = gblend;
    carry->weight0 = 1.0f - gblend;
    ReblendAsegbl(carry->pasegbl);
    QW target = posTarget.q;
    QW posJt = PosLoWorld(carry->pjt);
    SetStepRadTargetDir(carry->pjt, VectorSub(target, posJt));
    FixStepAngularVelocity__FP4STEP(carry->pjt);
}
