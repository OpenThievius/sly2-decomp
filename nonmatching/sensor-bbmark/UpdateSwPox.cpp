#include "types.h"
struct VT { char pad0[0x1B0]; s16 delta1B0; s16 index1B0; void (*fn1B4)(void *, void *, void *); char pad1[0x1F0 - 0x1B8]; s16 delta1F0; s16 index1F0; int (*fn1F4)(void *); };
struct OBJ { char pad0[0xC]; VT *vptr; };
struct OX { void *pmq; OX *next; OX *pair; OBJ *pobj; int flag; };
typedef OX NODE;
struct POXA { char pad0[0x60]; OBJ *pobj; NODE *head; };
struct SW;
extern "C" {
OX *AllocSwOx(SW *, POXA *, POXA *);
int FPoxaPairInteracts(SW *, POXA *, POXA *);
void FreeSlotheapPv(void *, void *);
void FreeSwMqList__FP2SWP2MQ(SW *, void *);
OX *PoxExtractFromPoxa(SW *, POXA *, POXA *);
void func_001F5078(OBJ *);
void UpdateSwPox(SW *psw, POXA *pa, POXA *pb, int mode)
{
    NODE *pnode = pa->head;
    if (pnode != 0) {
        if (pnode->pobj != pb->pobj) {
            do {
                pnode = pnode->next;
            } while (pnode != 0 && pnode->pobj != pb->pobj);
        }
    }
    int flag;
    switch (mode) {
    case 1: flag = 1; break;
    case 2: flag = 0; break;
    case 0: flag = 0; if (pnode) flag = pnode->flag; break;
    }
    NODE *pcur = pnode;
    if (flag != 0 || FPoxaPairInteracts(psw, pa, pb) != 0) {
        if (pcur == 0) {
            OX *pox = AllocSwOx(psw, pa, pb);
            OX *poxB = AllocSwOx(psw, pb, pa);
            pox->pair = poxB;
            poxB->pair = pox;
            pcur = pox;
        }
    } else {
        if (pcur == 0) return;
        OBJ *pobjA = pa->pobj;
        OBJ *pobjOther = pb->pobj;
        VT *pvtA = pobjA->vptr;
        void (*pfnA)(void *, void *, void *) = pvtA->fn1B4;
        pfnA((char *)pobjA + pvtA->delta1B0, pobjOther, pobjA);
        OBJ *pobjB = pb->pobj;
        OBJ *pobjOtherB = pa->pobj;
        VT *pvtB = pobjB->vptr;
        void (*pfnB)(void *, void *, void *) = pvtB->fn1B4;
        pfnB((char *)pobjB + pvtB->delta1B0, pobjOtherB, pobjB);
        OX *poxA = PoxExtractFromPoxa(psw, pa, pb);
        OX *poxB = PoxExtractFromPoxa(psw, pb, pa);
        void *pheap;
        if (poxA->pmq != 0) {
            FreeSwMqList__FP2SWP2MQ(psw, poxA->pmq);
            OBJ *pc = poxA->pobj;
            if (pc->vptr->fn1F4((char *)pc + pc->vptr->delta1F0) == 0)
                func_001F5078(poxA->pobj);
            OBJ *pd = poxB->pobj;
            if (pd->vptr->fn1F4((char *)pd + pd->vptr->delta1F0) == 0)
                func_001F5078(poxB->pobj);
        }
        pheap = (char *)psw + 0x3CF8;
        pcur = 0;
        FreeSlotheapPv(pheap, poxA);
        FreeSlotheapPv(pheap, poxB);
    }
    if (pcur != 0) {
        pcur->pair->flag = flag;
        pcur->flag = flag;
    }
}
}
