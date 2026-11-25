#include "sly2.h"
#include "cref.h"
struct CFrame;
extern "C" {
void FInvertMatrix4__FP7MATRIX4T0(MATRIX4 *, MATRIX4 *);
CRef RefOpMatrixInvert(int carg, CRef *aref, CFrame *pframe)
{
    CRef refInverse;
    refInverse.SetTag(TAGK_Matrix);
    FInvertMatrix4__FP7MATRIX4T0(aref[0].m_tag.m_pmatrix, refInverse.m_tag.m_pmatrix);
    return refInverse;
}
}
