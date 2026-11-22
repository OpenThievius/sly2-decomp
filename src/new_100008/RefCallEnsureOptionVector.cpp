// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct B8 { char b[8]; };
extern "C" void EnsureOptionVector(BASIC *, int, QW);
extern const B8 RO_002A3A60;

extern "C" CRef RefCallEnsureOptionVector(BASIC *object, int count, CRef *args)
{
    B8 aotyp = RO_002A3A60;
    VECTOR vec;
    int oid;
    RefSetArgsFromSplice(2, args, &aotyp, &oid, &vec);
    CRef ref;
    ref.SetTag(TAGK_Void);
    EnsureOptionVector(object, oid, *(QW *)&vec);
    return ref;
}
