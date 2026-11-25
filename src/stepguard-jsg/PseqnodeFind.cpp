// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "jsg.h"

struct SEQNODE_KEY {
    u8 unknown_0x0[0x10];
    int key;
};
struct SEQNODE {
    u8 unknown_0x0[0x28];
    SEQNODE_KEY *keyed;
    u8 unknown_0x2C[0xB8];
    SEQNODE *next;
};

SEQNODE *PseqnodeFind(JSG *owner, int key, SEQNODE *skip) {
    VECTOR local;
    SEQNODE *node;
    for (node = (SEQNODE *)owner->dlSeqnode.head; node != 0; node = node->next) {
        if (node != skip && node->keyed->key == key)
            return node;
    }
    return 0;
}
