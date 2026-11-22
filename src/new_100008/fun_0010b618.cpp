// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { char b[8]; int w; };
extern "C" void func_00185E30(BASIC *, QW, QW, QW);
extern const AOT RO_002A3F08;
CRef func_0010B618(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3F08;
    VECTOR q, r, s;
    RefSetArgsFromSplice(3, args, &aotyp, &q, &r, &s);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    func_00185E30(object, *(QW *)&q, *(QW *)&r, *(QW *)&s);
    return refResult;
}
