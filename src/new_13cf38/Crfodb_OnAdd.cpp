// SPDX-License-Identifier: GPL-3.0-or-later
#include "crfodb.h"
#include "sw.h"
struct ATTACHPT;
extern "C" {
void AttachPt_OnAdd(ATTACHPT *pattachpt);
void QueueSwCallbackOnce(void *psw, CRFODB *pcrfodb, s64 key, s32 arg);
extern SW B_003DD490; /* the world */
struct Unaligned64 { s64 v; } __attribute__((packed));
extern Unaligned64 RO_002A4BB0;
void Crfodb_OnAdd(CRFODB *pcrfodb) {
    AttachPt_OnAdd((ATTACHPT *)pcrfodb);
    QueueSwCallbackOnce(&B_003DD490, pcrfodb, RO_002A4BB0.v, 0);
}
}
