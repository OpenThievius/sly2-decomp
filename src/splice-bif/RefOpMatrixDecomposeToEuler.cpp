#include "sly2.h"
#include "cref.h"
struct CFrame;
struct Rows3;
extern "C" {
QW DecomposeRotateMatrixEuler(Rows3 *);
void CRef_ConstructVectorValue(CRef *, QW);
}
extern "C" CRef RefOpMatrixDecomposeToEuler(int carg, CRef *aref, CFrame *pframe)
{
    CRef refResult;
    CRef_ConstructVectorValue(&refResult, DecomposeRotateMatrixEuler((Rows3 *)aref[0].m_tag.m_pmatrix));
    return refResult;
}
