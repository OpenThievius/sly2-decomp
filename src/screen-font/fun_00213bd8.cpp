#include "fbsprite.h"
#include "sly2.h"
extern "C" void FStartSpriteDepthInstance(BLOT*, int, int, int, int, int);
extern "C" void func_00213BD8(BLOT* pblot, int label, int idDepth)
{
    for (int isprite = 0; isprite < pblot->csprite; isprite++) {
        SPRITE* psprite = &((SPRITE *)pblot->asprite)[isprite];
        for (int ilabel = 0; ilabel < psprite->clabel; ilabel++) {
            SPRITELABEL* plabel = &psprite->labels[ilabel];
            if (label == plabel->id) {
                FStartSpriteDepthInstance(pblot, isprite, ilabel, idDepth, 0, 0);
                return;
            }
        }
    }
}
