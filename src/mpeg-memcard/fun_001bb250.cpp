// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "so.h"
#include "sw.h"

struct CLS { int cid; int fEnabled; };
struct STG : SO { s32 ccls; CLS *acls; };
struct MQ;
struct STGITEM { MQ *pmq; STGITEM *pitemNext; s32 *pfActive; SO *pso; };
struct OXASTG { char unknown_0x0[0x64]; STGITEM *pitemFirst; };

extern SW B_003DD490;
extern "C" {
void func_001F4F10(SO *);
int FStgSwitchDone(STG *);
int FIsBasicDerivedFrom(void *, int);
void SetStgSwitchHitter(STG *, SO *, int);
void FreeSwMqList__FP2SWP2MQ(SW *, MQ *);
}

extern "C" void func_001BB250(STG *pstg)
{
    func_001F4F10(pstg);
    if (FStgSwitchDone(pstg))
        return;
    for (STGITEM *pitem = ((OXASTG *)pstg->poxa)->pitemFirst; pitem != 0; pitem = pitem->pitemNext) {
        if (*pitem->pfActive == 0)
            continue;
        for (int icls = 0; icls < pstg->ccls; icls++) {
            CLS *pcls = &pstg->acls[icls];
            if (pcls->fEnabled != 0 && FIsBasicDerivedFrom(pitem->pso, pcls->cid)) {
                if (!(pstg->grfso & 0x03000000))
                    SetStgSwitchHitter(pstg, pitem->pso, 0);
                if (FIsBasicDerivedFrom(pitem->pso, 0x62)) {
                    STG *pstgOther = (STG *)pitem->pso;
                    int iclsOther = 0;
                    while (iclsOther < pstgOther->ccls) {
                        CLS *pclsOther = &pstgOther->acls[iclsOther];
                        if (pclsOther->fEnabled != 0 && FIsBasicDerivedFrom(pstg, pclsOther->cid)) {
                            SetStgSwitchHitter(pstgOther, pstg, 0);
                            break;
                        }
                        iclsOther++;
                    }
                }
                pstg->Slot54(pitem->pso);
                pitem->pso->Slot54(pstg);
                FreeSwMqList__FP2SWP2MQ(&B_003DD490, pitem->pmq);
                *pitem->pfActive = 0;
                pitem->pmq = 0;
                break;
            }
        }
    }
}
