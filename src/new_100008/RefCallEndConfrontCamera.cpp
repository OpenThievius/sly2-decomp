// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct JSG;
struct AOT { int v[5]; };
extern "C" const AOT RO_002A3DF8;
extern "C" void AddSeqRecordEndConfrontCamera(JSG *, QW, QW, float, int, int);
CRef RefCallEndConfrontCamera(JSG *jsg, int count, CRef *args)
{
    AOT aotyp = RO_002A3DF8;
    VECTOR v0, v1;
    float g;
    int f0, f1;
    RefSetArgsFromSplice(5, args, &aotyp, &v0, &v1, &g, &f0, &f1);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    AddSeqRecordEndConfrontCamera(jsg, *(QW *)&v0, *(QW *)&v1, g, f0, f1);
    return refResult;
}
