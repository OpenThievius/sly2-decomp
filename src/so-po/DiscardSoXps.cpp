#include "sly2.h"
#include "so.h"
#include "oxa.h"
struct SW;
extern "C" void func_001F4BF8(SO *);
extern SW B_003DD490;
extern "C" void FreeSwMqList__FP2SWP2MQ(SW *, XP *); /* FreeSwMqList(SW *, MQ *): the symbol keeps the record's former name */
void DiscardSoXps(SO *pso)
{
    if (pso->poxa) {
        func_001F4BF8(pso);
        OX *link = pso->poxa->first;
        if (link) {
            do {
                SO *owner = pso->poxa->owner;
                owner->Slot54(link->pso);
                SO *other = link->pso;
                other->Slot54(pso->poxa->owner);
                FreeSwMqList__FP2SWP2MQ(&B_003DD490, link->pxp);
                link->pair->pxp = 0;
                link->pxp = 0;
                link = link->next;
            } while (link);
        }
        pso->Slot54(0);
        FreeSwMqList__FP2SWP2MQ(&B_003DD490, pso->poxa->own);
        pso->poxa->own = 0;
    }
}
