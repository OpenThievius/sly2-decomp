// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
extern "C" int func_00227C90(void *, QW);
extern "C" CRef func_00104718(void *self, int count, CRef *args)
{
    int aotyp[1] = {2};
    VECTOR vec;
    CRef ref = RefSetArgsFromSplice(1, args, aotyp, &vec);
    int inside = func_00227C90(self, *(QW *)&vec);
    ref.SetBool(inside != 0);
    return ref;
}
