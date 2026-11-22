// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "lo.h"
struct CLASSREC { char pad[0x10]; LO *(*pfnCreate)(); };
struct SWLOG { char pad[0x39E4]; LO **plog; };
extern "C" CLASSREC D_002BAAE8[];
extern "C" SWLOG B_003DD490;
extern "C" void *PframeFromSpliceBlock(SWLOG *, int, LO *);
extern "C" void CFramePtr_Assign(LO *, void *);
extern "C" void *PdlFromSwOid(SWLOG *, int);
extern "C" void *PdlFromSwCid(SWLOG *, int);
extern "C" void AppendSlEntry(void *, LO *);
extern "C" int FIsLoInWorld(LO *);

extern "C" LO *PloNew(int cid, SO *paloParent, int oid, int isplice)
{
    LO *plo = D_002BAAE8[cid].pfnCreate();
    plo->psoParent = paloParent;
    plo->oid = oid;
    CFramePtr_Assign(plo, PframeFromSpliceBlock(&B_003DD490, isplice, plo));
    AppendSlEntry(PdlFromSwOid(&B_003DD490, oid), plo);
    AppendSlEntry(PdlFromSwCid(&B_003DD490, cid), plo);
    plo->Init();
    if (((int)(plo->grfo >> 60) & 1) != 0)
        plo->AddHierarchy();
    if (FIsLoInWorld(plo) != 0)
        plo->Slot23();
    LO **plog = B_003DD490.plog;
    if (plog != 0) {
        *plog = plo;
        B_003DD490.plog = plog + 1;
    }
    return plo;
}
