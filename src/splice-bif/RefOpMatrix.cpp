#include "sly2.h"
#include "cref.h"
struct CPair { int cref; int pad4; CRef ref; CPair *next; };
struct CFrame;
extern "C" CRef CRef_RefCoerceF32(CRef *pref);
void *memset(void *, int, unsigned int);
extern "C" CRef RefOpMatrix(int carg, CRef *aref, CFrame *pframe)
{
    CRef refMatrix;
    refMatrix.SetTag(TAGK_Matrix);
    float *pg = (float *)refMatrix.m_tag.m_pmatrix;
    CPair *ppair;
    if (carg > 0) ppair = (CPair *)aref[0].m_tag.m_n;
    memset(pg, 0, 0x40);
    pg[15] = 1.0f;
    pg[10] = 1.0f;
    pg[5] = 1.0f;
    pg[0] = 1.0f;
    switch (carg) {
    case 0:
        break;
    case 1: {
        CRef refTemp = CRef_RefCoerceF32(&ppair->ref);
        float g = refTemp.m_tag.m_g;
        pg[10] = g;
        pg[5] = g;
        pg[0] = g;
        break;
    }
    case 3:
    case 4: {
        for (int irow = 0; irow < carg; irow++) {
            ((QW *)pg)[irow] = *(QW *)ppair->ref.m_tag.m_pvector;
            ppair = ppair->next;
        }
        break;
    }
    case 9:
    case 16: {
        int cdim = (carg == 9) ? 3 : 4;
        for (int irow = 0; irow < cdim; irow++) {
            for (int icol = 0; icol < cdim; icol++) {
                CRef refTemp = CRef_RefCoerceF32(&ppair->ref);
                pg[irow * 4 + icol] = refTemp.m_tag.m_g;
                ppair = ppair->next;
            }
        }
        break;
    }
    }
    return refMatrix;
}
