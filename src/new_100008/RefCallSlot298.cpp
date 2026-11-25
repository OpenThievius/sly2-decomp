#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct VT_10FC80 { u8 unknown_0x0[0x298]; s16 delta; s16 p; void (*fn)(char *); };
struct Obj_10FC80 { u8 unknown_0x0[0xC]; VT_10FC80 *vt; };
extern "C" CRef RefCallSlot298(Obj_10FC80 *obj, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    obj->vt->fn((char *)obj + obj->vt->delta);
    return refResult;
}
