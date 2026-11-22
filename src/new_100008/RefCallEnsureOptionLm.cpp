// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct B8 { char b[8]; };
extern "C" void EnsureOptionLm(BASIC *, int, void *);
extern const B8 RO_002A3A50;

extern "C" CRef RefCallEnsureOptionLm(BASIC *object, int count, CRef *args)
{
    B8 aotyp = RO_002A3A50;
    VECTOR vec;
    int oid;
    RefSetArgsFromSplice(2, args, &aotyp, &oid, &vec);
    CRef ref;
    ref.SetTag(TAGK_Void);
    EnsureOptionLm(object, oid, &vec);
    return ref;
}
