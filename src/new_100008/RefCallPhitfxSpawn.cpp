// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { char b[8]; };
extern "C" BASIC *PhitfxSpawn(BASIC *, QW, int);
extern const AOT RO_002A3F68;
CRef RefCallPhitfxSpawn(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3F68;
    VECTOR vec;
    int arg;
    CRef ref = RefSetArgsFromSplice(2, args, &aotyp, &vec, &arg);
    BASIC *spawned = PhitfxSpawn(object, *(QW *)&vec, arg);
    ref.SetBasic(spawned);
    return ref;
}
