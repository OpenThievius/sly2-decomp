// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
struct SW;
struct CFrame;
extern SW B_003DD490;
extern "C" {
void CStackFrame_Construct(void *);
void CStackFrame_Destructor(void *, int);
void IntersectSwBoundingSphere(SW *, QW, int, int, float, int *, int *);
void ExtractUniqueSosFromGeoms(int, int, int *, int *);
CRef RefFromAplo(int, int);
void CRef_CopyConstruct(CRef *, CRef *);
}
extern "C" CRef *RefOpFindObjectsInBoundingSphere(CRef *pret, int carg, CRef *aref, CFrame *pframe)
{
    CRef refResult;
    char frame[0x10];
    int cgeom;
    int ageom;
    int cplo;
    int aplo;
    float radius;
    refResult.m_tagk = TAGK_Nil;
    if (aref[1].m_tagk == TAGK_S32)
        radius = (float)aref[1].m_tag.m_n;
    else
        radius = aref[1].m_tag.m_g;
    CStackFrame_Construct(frame);
    IntersectSwBoundingSphere(&B_003DD490, *(QW *)aref[0].m_tag.m_pvector, 0, 0, radius, &cgeom, &ageom);
    ExtractUniqueSosFromGeoms(cgeom, ageom, &cplo, &aplo);
    {
        CRef refList = RefFromAplo(cplo, aplo);
        refResult = refList;
    }
    CRef_CopyConstruct(pret, &refResult);
    CStackFrame_Destructor(frame, 2);
    return pret;
}
