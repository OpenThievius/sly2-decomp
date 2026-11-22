/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The reference-counted boxes behind a CRef's pointer payloads. A CRef_Construct* or CRef_Set*Ptr
   allocates one from a slot heap (PvAllocSlotheapImpl), clears the count, points the CRef's payload at the value and
   increments the count; the value is copied in as one quadword (lq/sq) or four. The count sits after the value.
   Readers: CRef_ConstructVector, CRef_SetVectorPtr, CRef_SetVector (VECTORBOX); CRef_ConstructClq, CRef_SetClqPtr
   (CLQBOX); CRef_ConstructMatrix (MATRIXBOX). C and C++. */
#ifndef SLY2_CREFBOXES_H
#define SLY2_CREFBOXES_H
#include "sly2.h"
#include "cref.h"

struct SLOTHEAP;

/* the data of a CRef of tag Clq: one quadword, its fields not read by anyone yet */
struct CLQ {
    QW value;
};

struct VECTORBOX {
    struct VECTOR vector;
    s32 cref;
};

struct MATRIXBOX {
    struct MATRIX4 matrix;
    s32 cref;
};

struct CLQBOX {
    struct CLQ clq;
    s32 cref;
};

void *PvAllocSlotheapImpl(struct SLOTHEAP *pslotheap);
#endif
