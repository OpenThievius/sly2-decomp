#include "sly2.h"
#include "blot.h"
#include "blotsprite.h"
extern "C" {
int func_00218738(void *);
int func_00218710(void *);
int FBlotLabelPlaying(BLOT *pblot, int label)
{
    if (label == -1)
        return 0;
    if (pblot->cur == -1)
        return 0;
    if (label == 0x314)
        return func_00218738((void *)pblot->asprite) == 0;
    int isprite;
    for (isprite = 0; isprite < (int)pblot->csprite; isprite++) {
        BLOTSPRITE *psprite = &((BLOTSPRITE *)pblot->asprite)[isprite];
        int ilabel;
        for (ilabel = 0; ilabel < (int)psprite->clabel; ilabel++) {
            if (label == psprite->alabel[ilabel].id)
                return func_00218710(psprite);
        }
    }
    return 0;
}
}
