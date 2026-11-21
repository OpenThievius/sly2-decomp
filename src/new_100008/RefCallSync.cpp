#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
extern "C" void AddSeqRecordSync(BASIC *, void *);
CRef RefCallSync(BASIC *object, int count, CRef *args)
{
    int aotyp[1] = {0x8006};
    CRef value;
    value.m_tagk = TAGK_Nil;
    RefSetArgsFromSplice(1, args, aotyp, &value);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    AddSeqRecordSync(object, &value);
    return refResult;
}
