#include "sly2.h"
#include "sw.h"
struct AdjustStepXpsNode;
struct AdjustStep;
struct AdjustStepXpsHalf {
    char pad0[0xC];
    void *ownerStep;
    char pad1[0x30];
};
struct AdjustStepXpsLink {
    AdjustStepXpsNode *head;
    AdjustStepXpsLink *next;
    AdjustStepXpsNode **outHead;
};
struct AdjustStepXpsSet {
    char pad0[0x64];
    AdjustStepXpsLink *links;
    AdjustStepXpsNode *firstNode;
};
struct AdjustStepXpsNode {
    char pad0[0x8];
    AdjustStep *owner;
    void *ownerStep;
    char pad1[0x40 - 0x10];
    void *alternate;
    char pad2[0x50 - 0x48];
    QW quad;
    char pad3[0x90 - 0x60];
    float value;
    char pad4[0x9C - 0x94];
    int kind;
    char pad5[0xAC - 0xA0];
    AdjustStepXpsNode *next;
};
struct AdjustStep {
    char pad0[0xEC];
    AdjustStepXpsSet *set;
    char pad1[0x208 - 0xF0];
    AdjustStepXpsNode *chosen;
    float chosenScale;
    char pad2[0x230 - 0x210];
    QW chosenQuad;
};
extern "C" void func_001F4F10(void *);
extern "C" void FreeSwMqList__FP2SWP2MQ(SW *, AdjustStepXpsNode *);
extern "C" float g_2dded0;
extern "C" SW B_003DD490;

extern "C" void AdjustStepXps(AdjustStep *step)
{
    func_001F4F10(step);
    float bestValue = 3.4028235e38f;
    AdjustStepXpsNode *best = 0;
    AdjustStepXpsLink *link = step->set->links;
    for (;;) {
        AdjustStepXpsNode *node = link ? link->head : step->set->firstNode;
        for (; node; node = node->next) {
            if (node->kind == 0xE && node->value < bestValue) {
                bestValue = node->value;
                best = node;
            }
        }
        if (!link)
            break;
        link = link->next;
    }
    step->chosen = best;
    if (best) {
        step->chosenScale = g_2dded0;
        step->chosenQuad = best->quad;
    }
    AdjustStepXpsNode *removed = 0;
    link = step->set->links;
    for (;;) {
        AdjustStepXpsHalf *halves;
        AdjustStepXpsNode **slot = link ? &link->head : &step->set->firstNode;
        AdjustStepXpsNode *node = *slot;
        while (node) {
            halves = (AdjustStepXpsHalf *)node;
            int fOther = step != node->owner;
            AdjustStepXpsHalf *half = halves + fOther;
            if (half->ownerStep == step && node->kind == 0xE && node != best) {
                *slot = node->next;
                node->next = removed;
                removed = node;
            } else
                slot = &node->next;
            node = *slot;
        }
        if (!link)
            break;
        *link->outHead = link->head;
        link = link->next;
    }
    FreeSwMqList__FP2SWP2MQ(&B_003DD490, removed);
}
