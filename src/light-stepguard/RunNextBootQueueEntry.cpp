// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "bootq.h"
#include "cmpeg.h"
#include "memcardmenu.h"
struct SW;
extern SW B_003DD490;
extern CMpeg B_002F66B0;
extern char B_002DEB30;
extern MEMCARDMENU B_002E6550;
extern char D_002BFCA0;
extern "C" {
int FBootQueueHasEntries(BOOTQ *);
void QueueMovie(CMpeg *, MOVIE *);
void RequestTransition(SW *, void *, int, int, int, int);
void RestartAtTaskOid(void *, int, int);
void func_001ACC38(MEMCARDMENU *, int);
void RunNextBootQueueEntry(BOOTQ *);
}
extern "C" void RunNextBootQueueEntry__FP5BOOTQ(BOOTQ *pq)
{
    if (!FBootQueueHasEntries(pq))
        return;
    BOOTENTRY *pentry = &pq->aentry[pq->iEntryNext++];
    switch (pentry->kind) {
    case 0:
    case 1: {
        CMpeg *pmq = &B_002F66B0;
        QueueMovie(pmq, (MOVIE *)pentry->field_0x4);
        if (pentry->kind == 1)
            pmq->fSkippable = pentry->kind;
        RequestTransition(&B_003DD490, &D_002BFCA0, 0x189, -1, 0, -1);
        break;
    }
    case 2:
        RequestTransition(&B_003DD490, (void *)pentry->field_0x8, pentry->field_0xC, -1, pentry->field_0x10, 0x30A);
        break;
    case 3:
        RestartAtTaskOid(&B_002DEB30, pentry->field_0x14, pentry->field_0x18);
        break;
    case 5:
        if (B_002E6550.phase == 0)
            func_001ACC38(&B_002E6550, 1);
        RunNextBootQueueEntry(pq);
        break;
    }
}
