#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { char b[16]; };
extern "C" const AOT RO_002A4008;
extern "C" void AddTaskToggle(BASIC *, int, CRef *, int, int);
CRef RefCallAddTaskToggle(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A4008;
    int oid, parent, level;
    CRef states;
    states.m_tagk = TAGK_Nil;
    RefSetArgsFromSplice(4, args, &aotyp, &oid, &states, &parent, &level);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    AddTaskToggle(object, oid, &states, parent, level);
    return refResult;
}
