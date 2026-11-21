#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct VT { char pad[0x48]; s16 delta; s16 index; void (*fn)(void *); };
struct OBJ { char pad[0xC]; VT *vptr; };

CRef func_00100B88(OBJ *object, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef ref;
    ref.SetTag(TAGK_Void);
    VT *vtable = object->vptr;
    vtable->fn((char *)object + vtable->delta);
    return ref;
}
