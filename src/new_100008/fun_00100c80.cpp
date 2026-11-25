// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "so.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);

CRef func_00100C80(SO *object, int count, CRef *args)
{
    int aotyp[1];
    VECTOR vec;
    aotyp[0] = 2;
    CRef ref = RefSetArgsFromSplice(1, args, aotyp, &vec);
    int value = object->Slot73(*(QW *)&vec);
    ref.SetBool(value != 0);
    return ref;
}
