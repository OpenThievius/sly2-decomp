#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
/* slot 50 (SO::GetCpdefi in so.h) is called here without the CPDEFI it takes, so the class is not an SO: the raw call stays */
struct VT_10DB78 { u8 unknown_0x0[0x190]; s16 delta; s16 p; void (*fn)(char *); };
struct Obj_10DB78 { u8 unknown_0x0[0xC]; VT_10DB78 *vt; };
extern "C" CRef func_0010DB78(Obj_10DB78 *obj, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    obj->vt->fn((char *)obj + obj->vt->delta);
    return refResult;
}
