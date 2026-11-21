#include "sly2.h"
#include "cref.h"
#include "sw.h"
struct OBJ { char pad[0xC]; LO *plo; };
extern SW B_003DD490;
extern "C" void *PloFindSwObject(SW *, int, int, LO *, SCOPE *);

CRef RefOpFindNearestObject(int count, CRef *args, void *frame)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    LO *ploContext = (LO *)args[1].m_tag.m_pbasic;
    LO *pfound;
    if (args[2].m_tagk != 0)
        pfound = ((OBJ *)args[2].m_tag.m_n)->plo;
    else
        pfound = ploContext;
    SW *psw = &B_003DD490;
    int oid = args[0].m_tag.m_n;
    SCOPE *pscope;
    if (pfound != 0)
        pscope = pfound->pscope;
    else
        pscope = psw->pscopeDefault;
    refResult.SetBasic((BASIC *)PloFindSwObject(psw, 4, oid, ploContext, pscope));
    return refResult;
}
