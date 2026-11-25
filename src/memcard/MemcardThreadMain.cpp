#include "memcard.h"
extern "C" {
extern void ExitDeleteThread();
extern int SignalSema(int);
extern int WaitSema(int);
extern void *memset(void *, int, unsigned);
extern char B_002E65E0[];
extern int B_004425D8;

void MemcardThreadMain(MEMCARD *card) {
    WaitSema(card->semaphoreId);
    card->busy = card->pmf.pfn(card->pmf.delta + B_002E65E0);
    memset(&card->pmf, 0, 8);
    card->threadId = -1;
    B_004425D8 = -1;
    SignalSema(*(int *)card);
    ExitDeleteThread();
}

}
