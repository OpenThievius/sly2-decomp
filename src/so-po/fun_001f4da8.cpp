#include "sly2.h"
#include "xp.h"
extern "C" void func_001F5078(void);
extern "C" void FreeSwMqList__FP2SWP2MQ(void *, XP *);
extern "C" char B_003DD490;

extern "C" void func_001F4DA8(SO *a, SO *b, XP **link)
{
    XP *freed = 0;
    XP *node;
loop:
    node = *link;
    if (node != 0) {
        int sel = node->axpd[0].psoRoot == a; if (node->axpd[sel].psoRoot == b) {
            *link = node->pxpNext;
            node->pxpNext = freed;
            freed = node;
        } else {
            link = &node->pxpNext;
        }
        goto loop;
    }
    if (freed != 0) {
        func_001F5078();
        FreeSwMqList__FP2SWP2MQ(&B_003DD490, freed);
    }
}
