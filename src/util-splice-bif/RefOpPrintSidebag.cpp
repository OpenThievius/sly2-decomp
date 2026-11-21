#include "sly2.h"
#include "cref.h"
CRef *RefOpPrintSidebag(CRef *prefReturn)
{
    CRef refUnused;
    refUnused.m_tagk = TAGK_Nil;
    prefReturn->SetTag(TAGK_Void);
    return prefReturn;
}
