#include "fbsprite.h"
extern "C" {
extern SPRITESTAMP g_2ddf18;
void StopAmb(AMB *, float);
void VirtualRefPtr_Assign(AMB **, AMB *);
void ClearSpriteInstance(SPRITE *, int);
}
static inline void StopAmbRef(AMB **ppamb)
{
    if (ppamb != 0) {
        if (*ppamb != 0) {
            StopAmb(*ppamb, 0.0f);
            VirtualRefPtr_Assign(ppamb, 0);
        }
    }
}
extern "C" void StopSpriteInstance(SPRITE *psprite, int iinst)
{
    SPRITEINST *pinst = (SPRITEINST *)(iinst * sizeof(SPRITEINST) + (sptr)psprite->insts);
    if (pinst->ilabel >= 0) {
        int ilabel = pinst->ilabel;
        float t = pinst->t;
        psprite->ilabelStopped = ilabel;
        psprite->tStopped = t;
        psprite->stamp = g_2ddf18;
        psprite->ilabelPending = -1;
        pinst->fPaused = 0;
        pinst->ilabel = -1;
        StopAmbRef(&pinst->ramb.pamb);
    }
    ClearSpriteInstance(psprite, iinst);
}
