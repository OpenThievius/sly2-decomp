// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "so.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
/* an SO subclass of unknown class whose slot 78 takes an object and a vector (SO declares slots up to 75) */
struct SO_104E80 : SO {
    virtual void Slot76();
    virtual void Slot77();
    virtual void Slot78(int pobject, VECTOR *pvec);
};
struct AOT { int v[2]; };
extern const AOT RO_002A3BF0;
CRef T(SO_104E80 *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3BF0;
    int pobject;
    VECTOR vec;
    RefSetArgsFromSplice(2, args, &aotyp, &pobject, &vec);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    object->Slot78(pobject, &vec);
    return refResult;
}
