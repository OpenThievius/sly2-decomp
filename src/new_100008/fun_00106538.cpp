#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct AOT { int v[2]; };
extern "C" const AOT RO_002A3B98;
extern "C" void func_00170DA0(void *, int, int);

extern "C" CRef F106538(void *self, int count, CRef *args)
{
    AOT aotyp = RO_002A3B98;
    int first;
    int second;
    RefSetArgsFromSplice(2, args, &aotyp, &first, &second);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    func_00170DA0(self, first, second);
    return refResult;
}
