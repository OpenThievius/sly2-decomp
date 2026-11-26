#include "sly2.h"
#include "cref.h"
#include "sohit.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);

/* the Splice binding of SOHIT's slot 83 (option table of classes 71 to 76: SOHIT and its subclasses) */
extern "C" CRef RefCallSlot298(SOHIT *obj, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    obj->Slot83();
    return refResult;
}
