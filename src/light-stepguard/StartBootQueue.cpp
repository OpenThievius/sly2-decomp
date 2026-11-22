// SPDX-License-Identifier: GPL-3.0-or-later
#include "bootq.h"
struct MOVIE;
struct LEVEL;
extern "C" {
void AddBootQueueCardCheck(BOOTQ *);
void AddBootQueueLevel(BOOTQ *, LEVEL *, s32, s32);
void AddBootQueueMovie(BOOTQ *, MOVIE *);
void RunNextBootQueueEntry(BOOTQ *);
extern MOVIE RO_002A3868;
extern LEVEL RO_002A38A8;

void StartBootQueue(BOOTQ *pbootq) {
    pbootq->cEntry = 0;
    pbootq->iEntryNext = 0;
    AddBootQueueMovie(pbootq, &RO_002A3868);
    AddBootQueueCardCheck(pbootq);
    AddBootQueueLevel(pbootq, &RO_002A38A8, 0x189, 1);
    RunNextBootQueueEntry(pbootq);
}

}
