#include "cref.h"
/* a cell of a Splice list: a count, the value (car) and the next cell (cdr) */
struct CPair {
    /* 0x00 */ s32 cref;
    u8 unknown_0x4[0x4];
    /* 0x08 */ CRef ref;
    /* 0x10 */ CPair *next;
};

CRef *RefOpLength(CRef *arg0, int unused_a1, CRef *arg2) {
    int count;
    CPair *node;

    count = 0;
    if (arg2->m_tagk == TAGK_Pair) {
        node = arg2->m_tag.m_ppair;
        if (node != 0) {
            do {
                node = node->next;
                count += 1;
            } while (node != 0);
        }
    }
    arg0->m_tag.m_n = count;
    arg0->m_tagk = TAGK_S32;
    return arg0;
}
