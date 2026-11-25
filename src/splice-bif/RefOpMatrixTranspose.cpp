#include "sly2.h"
#include "cref.h"
struct CFrame;
extern "C" {
void CRef_ConstructMatrix(CRef *ref, MATRIX4 *matrix);
void TransposeMatrix4(MATRIX4 *dest, MATRIX4 *src);

CRef RefOpMatrixTranspose(int carg, CRef *aref, CFrame *pframe) {
    CRef refTranspose;
    MATRIX4 matrix;

    TransposeMatrix4(&matrix, aref[0].m_tag.m_pmatrix);
    CRef_ConstructMatrix(&refTranspose, &matrix);
    return refTranspose;
}

}
