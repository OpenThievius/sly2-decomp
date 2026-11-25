// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
struct VT { u8 unknown_0x0[0x60]; short delta; short index; int (*fn)(void *); };
struct OBJ { u8 unknown_0x0[0xC]; VT *vptr; };
#include "stepguard.h"
extern "C" u64 GrfsgsFromSgs(int);
extern "C" int func_002040F8(STEPGUARD *);

int GrfGuardCustomXps(STEPGUARD *pguard)
{
    if (pguard->grfsgs & GrfsgsFromSgs(0x14))
        return 1;
    u64 mask = GrfsgsFromSgs(0x12) | GrfsgsFromSgs(0x13) | GrfsgsFromSgs(0x16);
    if (pguard->grfsgs & mask)
        return 0;
    OBJ *pobj = (OBJ *)pguard->heading.field_0x0;
    if (pobj != 0)
        return pobj->vptr->fn((char *)pobj + pobj->vptr->delta);
    return func_002040F8(pguard);
}
