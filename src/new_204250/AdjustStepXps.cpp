#include "sly2.h"
#include "sw.h"
#include "laser.h"
#include "step.h"
#include "oxa.h"
/* one entry of the contact lists OXA::first points at: func_001F90D0 (SolveSw_file.cpp) reads head and next as its NODE; the
   third word is where this function writes the list's head back */
struct AdjustStepXpsLink {
    MQ *head;
    AdjustStepXpsLink *next;
    MQ **outHead;
};
extern "C" void func_001F4F10(void *);
extern "C" void FreeSwMqList__FP2SWP2MQ(SW *, MQ *);
extern "C" float g_2dded0;
extern "C" SW B_003DD490;
extern "C" void AdjustStepXps(STEP *step)
{
    func_001F4F10(step);
    float bestValue = 3.4028235e38f;
    MQ *best = 0;
    AdjustStepXpsLink *link = (AdjustStepXpsLink *)step->poxa->first;
    for (;;) {
        MQ *node = link ? link->head : (MQ *)step->poxa->own;
        for (; node; node = node->pmqNext) {
            if (node->kind == 0xE && node->gScale < bestValue) {
                bestValue = node->gScale;
                best = node;
            }
        }
        if (!link)
            break;
        link = link->next;
    }
    step->psoSurface = (SO *)best;
    if (best) {
        step->tJump = g_2dded0;
        step->posWorld = best->aside[1].pos;
    }
    MQ *removed = 0;
    link = (AdjustStepXpsLink *)step->poxa->first;
    for (;;) {
        MQ **slot = link ? &link->head : (MQ **)&step->poxa->own;
        MQ *node = *slot;
        while (node) {
            int fOther = (SO *)step != node->aside[0].plo;
            if (node->aside[fOther].pso == (int)step && node->kind == 0xE && node != best) {
                *slot = node->pmqNext;
                node->pmqNext = removed;
                removed = node;
            } else
                slot = &node->pmqNext;
            node = *slot;
        }
        if (!link)
            break;
        *link->outHead = link->head;
        link = link->next;
    }
    FreeSwMqList__FP2SWP2MQ(&B_003DD490, removed);
}
