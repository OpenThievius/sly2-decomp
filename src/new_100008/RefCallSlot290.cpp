#include "sly2.h"
#include "cref.h"
#include "sohit.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);

/* the Splice binding of SOHIT's slot 82 (option table of classes 71 to 76: SOHIT and its subclasses) */
CRef RefCallSlot290(SOHIT *object, int count, CRef *args)
{
    int aotyp[1];
    int arg;
    aotyp[0] = 0x2030;
    RefSetArgsFromSplice(1, args, aotyp, &arg);
    CRef ref;
    ref.SetTag(TAGK_Void);
    object->Slot82(arg);
    return ref;
}
