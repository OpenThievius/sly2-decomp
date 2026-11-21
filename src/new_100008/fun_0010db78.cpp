#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct VT_10DB78 { char pad[0x190]; s16 delta; s16 p; void (*fn)(char *); };
struct Obj_10DB78 { int pad[3]; VT_10DB78 *vt; };
extern "C" CRef func_0010DB78(Obj_10DB78 *obj, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    obj->vt->fn((char *)obj + obj->vt->delta);
    return refResult;
}
