#include "sly2.h"
#include "cref.h"
#include "lo.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);

CRef func_00100A90(LO *object, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef ref;
    ref.SetTag(TAGK_Void);
    object->Add();
    return ref;
}
