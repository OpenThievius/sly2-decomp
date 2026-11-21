// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
struct SW;
struct CFrame;
extern SW B_003DD490;
extern "C" {
void CStackFrame_Construct(void *);
void CStackFrame_Destructor(void *, int);
void bevy_camera_follow_push_out(SW *, QW, QW, int, int, int *, int *);
void ExtractUniqueSosFromGeoms(int, int, int *, int *);
CRef RefFromAplo(int, int);
void CRef_CopyConstruct(CRef *, CRef *);
}
extern "C" CRef *RefOpFindObjectsInBoundingBox(CRef *pret, int carg, CRef *aref, CFrame *pframe)
{
    CRef refResult;
    char frame[0x10];
    int cgeom;
    int ageom;
    int cplo;
    int aplo;
    refResult.m_tagk = TAGK_Nil;
    CStackFrame_Construct(frame);
    bevy_camera_follow_push_out(&B_003DD490, *(QW *)aref[0].m_tag.m_pvector, *(QW *)aref[1].m_tag.m_pvector, 0, 0, &cgeom, &ageom);
    ExtractUniqueSosFromGeoms(cgeom, ageom, &cplo, &aplo);
    {
        CRef refList = RefFromAplo(cplo, aplo);
        refResult = refList;
    }
    CRef_CopyConstruct(pret, &refResult);
    CStackFrame_Destructor(frame, 2);
    return pret;
}
