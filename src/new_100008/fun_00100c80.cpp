// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct VT { char pad[584]; short delta; short index; int (*fn)(void *, QW); };
struct OBJ { char pad[0xC]; VT *vptr; };

CRef func_00100C80(OBJ *object, int count, CRef *args)
{
    int aotyp[1];
    VECTOR vec;
    aotyp[0] = 2;
    CRef ref = RefSetArgsFromSplice(1, args, aotyp, &vec);
    VT *vtable = object->vptr;
    int value = vtable->fn((char *)object + vtable->delta, *(QW *)&vec);
    ref.SetBool(value != 0);
    return ref;
}
