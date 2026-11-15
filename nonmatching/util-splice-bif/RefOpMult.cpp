#include "types.h"
#include "ps2inline.h"
#include "vu0inline.h"
#include "cref.h"
struct CFrame;
/* a list cell of Splice: the argument after the first is held at +8, the next cell at +0x10 */
struct CPair { int m_cref; int m_unknown4; CRef m_ref; CPair *m_ppairNext; };
struct LM { float gMin; float gMax; };
union VU_SCALE { QW q; VECTOR v; };
struct VU_FLOAT { QW m_q; VU_FLOAT(float g); };
struct VU_VECTOR { QW m_q; VU_VECTOR(const VECTOR &vector); };
VU_VECTOR operator*(VU_FLOAT vuf, VU_VECTOR vuv);
MATRIX4 operator*(const MATRIX4 &matrixLeft, const MATRIX4 &matrixRight);
extern "C" {
CRef *CRef_SetF32(CRef *pref, float g);
CRef *CRef_SetVector(CRef *pref, QW vector);
CRef *CRef_SetMatrixPtr(CRef *pref, MATRIX4 *pmatrix);
CRef *CRef_RefClone(CRef *pref, CRef *ref, CFrame *pframe, unsigned long ulArg);
VECTOR *__as__6VECTORG9VU_VECTOR(VECTOR *pvector, VU_VECTOR vuv);
}

static inline void MultiplyVector(VECTOR *pvector, QW q)
{
    VU_SCALE scale;
    scale.q = q;
    *(QW *)pvector = VectorScaleX(*(QW *)pvector, scale.q);
}

static inline void MultiplyLm(LM *plm, float g)
{
    plm->gMin = plm->gMin * g;
    plm->gMax = plm->gMax * g;
}

static inline void MultiplyMatrix(MATRIX4 *pmatrix, float g)
{
    MATRIX4 matrix;
    VU_SCALE scale;
    scale.q = QuadFromFloat(g);
    float gScale = LaneX(scale.q);
    float *pgDst = &matrix.mat[0][0];
    float *pgSrc = &pmatrix->mat[0][0];
    for (int i = 0; i < 16; i++)
        pgDst[i] = gScale * pgSrc[i];
    *pmatrix = matrix;
}

static inline void MultiplyClq(CLQ *pclq, float g)
{
    __as__6VECTORG9VU_VECTOR((VECTOR *)pclq, VU_FLOAT(g) * VU_VECTOR(*(VECTOR *)pclq));
}

CRef RefOpMult(int cref, CRef *aref)
{
    CRef ref;
    ref.m_tagk = TAGK_Nil;
    int fInteger = 0;
    switch (aref->m_tagk) {
    case TAGK_S32:
        CRef_SetF32(&ref, (float)aref->m_tag.m_n);
        fInteger = 1;
        break;
    case TAGK_F32:
    case TAGK_Vector:
    case TAGK_Matrix:
    case TAGK_Clq:
    case TAGK_Lm: {
        CRef refClone;
        CRef_RefClone(&refClone, aref, 0, 0);
        ref = refClone;
        break;
    }
    }
    CPair *ppair = 0;
    if (aref[1].m_tagk != 0)
        ppair = aref[1].m_tag.m_ppair;
    for (; ppair != 0; ppair = ppair->m_ppairNext) {
        CRef *prefArg = &ppair->m_ref;
        switch (ref.m_tagk) {
        case TAGK_F32:
            switch (prefArg->m_tagk) {
            case TAGK_F32:
                ref.m_tag.m_g = ref.m_tag.m_g * prefArg->m_tag.m_g;
                fInteger = 0;
                break;
            case TAGK_S32:
                ref.m_tag.m_g = ref.m_tag.m_g * (float)prefArg->m_tag.m_n;
                break;
            case TAGK_Vector: {
                VU_SCALE scale;
                scale.q = VectorFromFloat(ref.m_tag.m_g);
                QW vector = VectorScaleX(*(QW *)prefArg->m_tag.m_pvector, scale.q);
                CRef_SetVector(&ref, vector);
                break;
            }
            case TAGK_Matrix: {
                MATRIX4 matrix;
                float *pgSrc = &prefArg->m_tag.m_pmatrix->mat[0][0];
                VU_SCALE scale;
                scale.q = QuadFromFloat(ref.m_tag.m_g);
                float gScale = LaneX(scale.q);
                float *pgDst = &matrix.mat[0][0];
                for (int i = 0; i < 16; i++)
                    pgDst[i] = gScale * pgSrc[i];
                CRef_SetMatrixPtr(&ref, &matrix);
                break;
            }
            case TAGK_Clq: {
                float g = ref.m_tag.m_g;
                ref.Decref();
                ref.SetTag(TAGK_Clq);
                VECTOR *pvectorDst = (VECTOR *)ref.m_tag.m_pclq;
                VECTOR *pvectorSrc = (VECTOR *)prefArg->m_tag.m_pclq;
                __as__6VECTORG9VU_VECTOR(pvectorDst, VU_FLOAT(g) * VU_VECTOR(*pvectorSrc));
                break;
            }
            case TAGK_Lm: {
                float g = ref.m_tag.m_g;
                ref.Decref();
                ref.SetTag(TAGK_Lm);
                LM *plmSrc = prefArg->m_tag.m_plm;
                LM *plmDst = ref.m_tag.m_plm;
                plmDst->gMin = plmSrc->gMin * g;
                plmDst->gMax = plmSrc->gMax * g;
                break;
            }
            }
            break;
        case TAGK_Vector:
            switch (prefArg->m_tagk) {
            case TAGK_S32:
                MultiplyVector(ref.m_tag.m_pvector, VectorFromFloat((float)prefArg->m_tag.m_n));
                break;
            case TAGK_F32:
                MultiplyVector(ref.m_tag.m_pvector, VectorFromWord(*(u32 *)&prefArg->m_tag.m_g));
                break;
            }
            break;
        case TAGK_Matrix:
            switch (prefArg->m_tagk) {
            case TAGK_S32:
                MultiplyMatrix(ref.m_tag.m_pmatrix, (float)prefArg->m_tag.m_n);
                break;
            case TAGK_F32:
                MultiplyMatrix(ref.m_tag.m_pmatrix, prefArg->m_tag.m_g);
                break;
            case TAGK_Vector: {
                MATRIX4 *pmatrix = ref.m_tag.m_pmatrix;
                QW vector = TransformPoint(*(QW *)prefArg->m_tag.m_pvector, *(QW *)&pmatrix->mat[0][0],
                                                                       *(QW *)&pmatrix->mat[1][0], *(QW *)&pmatrix->mat[2][0],
                                                                       *(QW *)&pmatrix->mat[3][0]);
                CRef_SetVector(&ref, vector);
                break;
            }
            case TAGK_Matrix: {
                MATRIX4 *pmatrix = ref.m_tag.m_pmatrix;
                *pmatrix = *pmatrix * *prefArg->m_tag.m_pmatrix;
                break;
            }
            }
            break;
        case TAGK_Clq:
            switch (prefArg->m_tagk) {
            case TAGK_S32:
                MultiplyClq(ref.m_tag.m_pclq, (float)prefArg->m_tag.m_n);
                break;
            case TAGK_F32:
                MultiplyClq(ref.m_tag.m_pclq, prefArg->m_tag.m_g);
                break;
            }
            break;
        case TAGK_Lm:
            switch (prefArg->m_tagk) {
            case TAGK_S32:
                MultiplyLm(ref.m_tag.m_plm, (float)prefArg->m_tag.m_n);
                break;
            case TAGK_F32:
                MultiplyLm(ref.m_tag.m_plm, prefArg->m_tag.m_g);
                break;
            }
            break;
        }
    }
    if (fInteger != 0 && ref.m_tagk == TAGK_F32)
        ref.SetS32((int)ref.m_tag.m_g);
    return ref;
}
