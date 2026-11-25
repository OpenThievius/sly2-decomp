#include "sly2.h"
#include "cref.h"
#include "jt.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" CRef *CRef_SetBool(CRef *, int);

CRef bevy_game_methods_cls_10b028(JT *object, int count, CRef *args)
{
    int aotyp[1];
    int arg;
    aotyp[0] = 0x1057;
    RefSetArgsFromSplice(1, args, aotyp, &arg);
    CRef ref;
    ref.SetTag(TAGK_Void);
    object->SetMode(arg);
    return ref;
}
