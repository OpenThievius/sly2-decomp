// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "stepguard.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct AOT { int v[2]; };
extern "C" const AOT RO_002A3B80;
extern "C" void func_00154038(SENSOR *, int, int);

CRef func_00104060(STEPGUARD *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3B80;
    int oid;
    int state;
    RefSetArgsFromSplice(2, args, &aotyp, &oid, &state);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    func_00154038(object->psensor, oid, state);
    return refResult;
}
