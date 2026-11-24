/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "cref.h"
/* a cell of a Splice list: a count, the value (car) and the next cell (cdr) */
struct CPair {
    /* 0x00 */ s32 cref;
    u8 unknown_0x4[0x4];
    /* 0x08 */ CRef ref;
    /* 0x10 */ CPair *next;
};
extern "C" {
CRef *func_001255F0(CRef *arg0, s32 arg1, CRef *arg2) {
    s32 mask = -1;
    CPair *node = 0;

    if (arg2->m_tagk != 0) {
        node = arg2->m_tag.m_ppair;
    }
    if (node != 0) {
        do {
            mask &= node->ref.m_tag.m_n;
            node = node->next;
        } while (node != 0);
    }
    arg0->m_tag.m_n = mask;
    arg0->m_tagk = TAGK_S32;
    return arg0;
}
}
