// SPDX-License-Identifier: GPL-3.0-or-later
#include "dprize.h"
#include "swfind.h"

extern "C" {
extern SW B_003DD490;
void PostSoLoad(DPRIZE *);
LO *PloFindSwObjectByClass(SW *psw, unsigned grffso, int cid, LO *ploContext);
}
void PostDprizeLoad(DPRIZE *pdprize)
{
    PostSoLoad(pdprize);
    LO *ploShadow = PloFindSwObjectByClass(&B_003DD490, 1, 0x12, pdprize);
    pdprize->ploShadow = ploShadow;
    if (ploShadow != 0) {
        ploShadow->Remove();
    }
    if (pdprize->aoidploGlint[0].oid != -1)
        pdprize->aoidploGlint[0].plo = PloFindSwObject_thunk(&B_003DD490, 4, pdprize->aoidploGlint[0].oid, pdprize);
    if (pdprize->aoidploGlint[1].oid != -1)
        pdprize->aoidploGlint[1].plo = PloFindSwObject_thunk(&B_003DD490, 4, pdprize->aoidploGlint[1].oid, pdprize);
    if (pdprize->aoidploGlint[2].oid != -1)
        pdprize->aoidploGlint[2].plo = PloFindSwObject_thunk(&B_003DD490, 4, pdprize->aoidploGlint[2].oid, pdprize);
    if (pdprize->aoidploB[0].oid != -1)
        pdprize->aoidploB[0].plo = PloFindSwObject_thunk(&B_003DD490, 4, pdprize->aoidploB[0].oid, pdprize);
    if (pdprize->aoidploB[1].oid != -1)
        pdprize->aoidploB[1].plo = PloFindSwObject_thunk(&B_003DD490, 4, pdprize->aoidploB[1].oid, pdprize);
    if (pdprize->aoidploB[2].oid != -1)
        pdprize->aoidploB[2].plo = PloFindSwObject_thunk(&B_003DD490, 4, pdprize->aoidploB[2].oid, pdprize);
    pdprize->SetDprizes(pdprize->dprizesInitial);
}
