#include "sly2.h"

struct SEQNODE_KEY {
    char pad0[0x10];
    int key;
};
struct SEQNODE {
    char pad0[0x28];
    SEQNODE_KEY *keyed;
    char pad1[0xB8];
    SEQNODE *next;
};
struct SEQNODE_OWNER {
    char pad0[0x5C];
    SEQNODE *first;
};

SEQNODE *PseqnodeFind(SEQNODE_OWNER *owner, int key, SEQNODE *skip) {
    VECTOR local;
    SEQNODE *node;
    for (node = owner->first; node != 0; node = node->next) {
        if (node != skip && node->keyed->key == key)
            return node;
    }
    return 0;
}
