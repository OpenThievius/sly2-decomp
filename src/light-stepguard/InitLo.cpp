// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "so.h"
extern SCOPE *B_003E139C;
extern "C" {
void func_001A53A0(LO *);
void func_001A5448(LO *, int *, int **);
void InsertDlEntryBefore(int, int, LO *);
}
extern "C" void InitLo__FP2LO(LO *plo)
{
    int *pdl;
    int *ppfirst;
    SO *pparent = plo->psoParent;
    plo->field_0x38 = 1.0e10f;
    u64 grf = plo->grfo;
    grf |= 0x000F000000000000UL;
    grf &= ~0x00F0000000000000UL;
    grf |= 0x0020000000000000UL;
    plo->grfo = grf;
    ((unsigned char *)plo)[0x2D] = 0xFF;
    if (pparent != 0) {
        plo->proot = pparent->proot;
        unsigned bit = (unsigned)(pparent->grfo >> 60) & 1;
        plo->grfo = (plo->grfo & ~0x1000000000000000UL) | ((u64)bit << 60);
    } else {
        func_001A53A0(plo);
        plo->grfo |= 0x1000000000000000UL;
    }
    plo->grfSw = 0x21;
    SCOPE *pscope;
    if (plo->psoParent)
        pscope = plo->psoParent->pscope;
    else
        pscope = B_003E139C;
    plo->pscope = pscope;
    func_001A5448(plo->psoParent, (int *)&pdl, (int **)&ppfirst);
    InsertDlEntryBefore((sptr)pdl, *ppfirst, plo);
}
