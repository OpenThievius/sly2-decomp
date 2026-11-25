#include "sly2.h"
#include "so.h"
#include "oxa.h"
struct NODE { int pmq; NODE *next; int *pcount; SO *pso; };
struct SW;
struct MQ;
extern "C" void func_001F4BF8(SO *);
extern SW B_003DD490;
void FreeSwMqList(SW *, MQ *);
void DiscardSoXps(SO *pso)
{
    if (pso->poxa) {
        func_001F4BF8(pso);
        NODE *link = pso->poxa->first;
        if (link) {
            do {
                SO *owner = pso->poxa->owner;
                owner->Slot54(link->pso);
                SO *other = link->pso;
                other->Slot54(pso->poxa->owner);
                FreeSwMqList(&B_003DD490, (MQ *)link->pmq);
                *link->pcount = 0;
                link->pmq = 0;
                link = link->next;
            } while (link);
        }
        pso->Slot54(0);
        FreeSwMqList(&B_003DD490, (MQ *)pso->poxa->own);
        pso->poxa->own = 0;
    }
}
