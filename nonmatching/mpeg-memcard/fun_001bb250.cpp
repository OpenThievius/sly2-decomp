// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "so.h"

struct CLS { int cid; int pad; };
struct STG : SO { s32 count; CLS *classes; };
struct STGITEM { void *pmq; STGITEM *next; s32 *pflag; SO *pso; };
struct OXAX { char pad[0x64]; STGITEM *pitemFirst; };

extern "C" {
void func_001F4F10(SO *);
int FStgSwitchDone(STG *);
int FIsBasicDerivedFrom(void *, int);
void SetStgSwitchHitter(STG *, void *, int);
void FreeSwMqList__FP2SWP2MQ(void *, void *);
}
extern "C" char B_003DD490[];

extern "C" void func_001BB250(STG *stg)
{
    func_001F4F10(stg);
    if (FStgSwitchDone(stg))
        return;
    for (STGITEM *item = ((OXAX *)stg->poxa)->pitemFirst; item != 0; item = item->next) {
        if (*item->pflag != 0 && stg->count > 0) {
            int index = 0;
            do {
                CLS *entry = &stg->classes[index];
                if (entry->pad != 0 && FIsBasicDerivedFrom(item->pso, entry->cid)) {
                    if (!(stg->grfso & 0x03000000))
                        SetStgSwitchHitter(stg, item->pso, 0);
                    if (FIsBasicDerivedFrom(item->pso, 0x62)) {
                        STG *other = (STG *)item->pso;
                        int j = 0;
                        while (j < other->count) {
                            CLS *entryOther = &other->classes[j];
                            if (entryOther->pad != 0 && FIsBasicDerivedFrom(stg, entryOther->cid)) {
                                SetStgSwitchHitter(other, stg, 0);
                                break;
                            }
                            j++;
                        }
                    }
                    stg->Slot54(item->pso);
                    item->pso->Slot54(stg);
                    FreeSwMqList__FP2SWP2MQ(B_003DD490, item->pmq);
                    *item->pflag = 0;
                    item->pmq = 0;
                    break;
                }
                index++;
            } while (index < stg->count);
        }
    }
}
