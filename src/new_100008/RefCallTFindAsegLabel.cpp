// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct ASEG;
extern "C" float TFindAsegLabel__FP4ASEG3OID(ASEG *, int);

extern "C" CRef RefCallTFindAsegLabel(ASEG *object, int count, CRef *args)
{
    int aotyp = 6;
    int oid;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &oid);
    refResult.SetF32(TFindAsegLabel__FP4ASEG3OID(object, oid));
    return refResult;
}
