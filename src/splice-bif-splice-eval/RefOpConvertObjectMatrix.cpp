#include "sly2.h"
#include "cref.h"
struct CFrame;
extern "C" MATRIX4 ConvertAloMat(int, int, MATRIX4 *);

CRef RefOpConvertObjectMatrix(int carg, CRef *aref, CFrame *pframe)
{
    CRef refResult;
    refResult.SetTag(TAGK_Matrix);
    MATRIX4 *pdest = refResult.m_tag.m_pmatrix;
    MATRIX4 mat = ConvertAloMat(aref[0].m_tag.m_n, aref[1].m_tag.m_n, aref[2].m_tag.m_pmatrix);
    *pdest = mat;
    return refResult;
}
