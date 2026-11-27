#include "sly2.h"
#include "sw.h"
#include "laser.h"
#include "xp.h"
#include "step.h"
#include "oxa.h"
extern "C" void func_001F4F10(void *);
extern "C" void FreeSwMqList__FP2SWP2MQ(SW *, XP *);
extern "C" float g_2dded0;
extern "C" SW B_003DD490;
extern "C" void AdjustStepXps(STEP *step)
{
    func_001F4F10(step);
    float bestValue = 3.4028235e38f;
    XP *best = 0;
    OX *link = step->poxa->first;
    for (;;) {
        XP *node = link ? link->pxp : step->poxa->own;
        for (; node; node = node->pxpNext) {
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
        step->posWorld = best->axpd[1].pos;
    }
    XP *removed = 0;
    link = step->poxa->first;
    for (;;) {
        XP **slot = link ? &link->pxp : &step->poxa->own;
        XP *node = *slot;
        while (node) {
            int fOther = step != node->axpd[0].psoRoot;
            if (node->axpd[fOther].pso == step && node->kind == 0xE && node != best) {
                *slot = node->pxpNext;
                node->pxpNext = removed;
                removed = node;
            } else
                slot = &node->pxpNext;
            node = *slot;
        }
        if (!link)
            break;
        link->pair->pxp = link->pxp;
        link = link->next;
    }
    FreeSwMqList__FP2SWP2MQ(&B_003DD490, removed);
}
