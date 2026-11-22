// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct B8 { char b[8]; };
extern "C" void func_001F82B8(BASIC *, int, void *);
extern const B8 RO_002A3A90;

extern "C" CRef func_00101608(BASIC *object, int count, CRef *args)
{
    B8 aotyp = RO_002A3A90;
    VECTOR vec;
    int oid;
    RefSetArgsFromSplice(2, args, &aotyp, &oid, &vec);
    CRef ref;
    ref.SetTag(TAGK_Void);
    func_001F82B8(object, oid, &vec);
    return ref;
}
