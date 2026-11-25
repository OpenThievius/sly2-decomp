#include "sw.h"
/* an ASHLIST entry (button.h) once loaded: the object id is replaced by the object the load finds for it */
struct ASHENTRYLOADED {
    union {
        s32 oid;
        LO *plo;
    };
    s32 nArg;
};
struct ASHLISTLOADED {
    s32 count;
    ASHENTRYLOADED aentry[8];
};
extern "C" SW B_003DD490;
extern "C" LO *PloFindSwObject_thunk(SW *, int, int, void *);
void PostAshLoad(ASHLISTLOADED *list, void *owner)
{
    for (int index = 0; index < list->count; index++) {
        ASHENTRYLOADED *pentry = &list->aentry[index];
        LO *obj = PloFindSwObject_thunk(&B_003DD490, 4, pentry->oid, owner);
        if (obj != 0) {
            pentry->plo = obj;
            obj->Remove();
        } else {
            pentry->plo = 0;
        }
    }
}
