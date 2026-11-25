#include "sly2.h"
struct N_1F4DA8 { u8 unknown_0x0[8]; int key; u8 unknown_0xC[0xA0]; N_1F4DA8 *next; };
extern "C" void func_001F5078(void);
extern "C" void FreeSwMqList__FP2SWP2MQ(void *, N_1F4DA8 *);
extern "C" char B_003DD490;

extern "C" void func_001F4DA8(int a, int b, N_1F4DA8 **link)
{
    N_1F4DA8 *freed = 0;
    N_1F4DA8 *node;
loop:
    node = *link;
    if (node != 0) {
        int sel = node->key == a; if (((N_1F4DA8 *)((char *)node + (sel << 6)))->key == b) {
            *link = node->next;
            node->next = freed;
            freed = node;
        } else {
            link = &node->next;
        }
        goto loop;
    }
    if (freed != 0) {
        func_001F5078();
        FreeSwMqList__FP2SWP2MQ(&B_003DD490, freed);
    }
}
