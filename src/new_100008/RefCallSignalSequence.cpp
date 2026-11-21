#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { char b[8]; };
extern "C" const AOT RO_002A3C70;
extern "C" void AddSeqRecordSignalSequence(void *, int, int);
extern "C" CRef F106D50(void *self, int count, CRef *args)
{
    AOT aotyp = RO_002A3C70;
    int first, second;
    RefSetArgsFromSplice(2, args, &aotyp, &first, &second);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    AddSeqRecordSignalSequence(self, first, second);
    return refResult;
}
