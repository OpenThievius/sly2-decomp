#include "sly2.h"
#include "cref.h"
struct CFrame;
#include "sw.h"
struct CPair { int pad0; int pad4; CRef ref; };
extern SW B_003DD490;
extern "C" int PloFindSwObject(SW *, int, int, LO *, SCOPE *);

CRef RefOpFindObject(int carg, CRef *aref, CFrame *pframe)
{
    CRef refResult;
    LO *basis = (LO *)aref[1].m_tag.m_n;
    refResult.m_tagk = TAGK_Nil;
    LO *scopeObject;
    if (aref[2].m_tagk != 0)
        scopeObject = (LO *)((CPair *)aref[2].m_tag.m_n)->ref.m_tag.m_n;
    else
        scopeObject = basis;
    SW *psw = &B_003DD490;
    int grffso = 5;
    if (basis != 0)
        grffso = 1;
    int id = aref[0].m_tag.m_n;
    SCOPE *pscope;
    if (scopeObject != 0)
        pscope = scopeObject->pscope;
    else
        pscope = psw->pscopeDefault;
    int found = PloFindSwObject(psw, grffso, id, basis, pscope);
    refResult.SetBasic((BASIC *)found);
    return refResult;
}
