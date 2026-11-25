#include "sly2.h"
struct Node { u8 unknown_0x0[0x10]; s32 mark; u8 unknown_0x14[4]; Node *next; };
struct CSplotheap { Node *head; };
extern "C" void UnmarkAll__10CSplotheap(CSplotheap *self)
{
    Node *node = self->head;
    while (node) {
        node->mark = 0;
        node = node->next;
    }
}
