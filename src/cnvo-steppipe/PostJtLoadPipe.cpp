// SPDX-License-Identifier: GPL-3.0-or-later
#include "asega.h"
/* two blend entries of an animation each: the aseg, its speed from the start and end of its first channel */
struct PIPEBLENDENTRY { ASEG *pasegUnused; ASEG *paseg; s32 field_0x8; float speed; };
/* the object PostJtLoadPipe prepares: a Jt, then two entries from 0x50 and a word EnsureAsegBlendDynamic fills at 0x70 */
struct JTPIPEBLEND {
    void *pjt;
    u8 unknown_0x4[0x4C];
    PIPEBLENDENTRY aent[2];
    s32 unk70;
};
extern "C" {
ASEGCHN *PchnFindAseg(ASEG *, void *, int, int);
void EnsureAsegBlendDynamic(void *, int, int, void *, int, void *, void *, void *);
}
void PostJtLoadPipe(JTPIPEBLEND *ppipe)
{
    float agStart[4];
    float agEnd[4];
    int i = 1;
    PIPEBLENDENTRY *pent = &ppipe->aent[0];
    do {
        ASEG *paseg = pent->paseg;
        if (paseg != 0) {
            ASEGCHN *pchn = PchnFindAseg(paseg, ppipe->pjt, 1, 1);
            if (pchn != 0) {
                pchn->panim->GetValues(0.0f, 1.0f, agStart, 0);
                pchn->panim->GetValues(paseg->tLength, 1.0f, agEnd, 0);
                pent->speed = (agStart[2] - agEnd[2]) / paseg->tLength;
            }
        }
        pent++;
    } while (--i >= 0);
    EnsureAsegBlendDynamic(ppipe->pjt, 0x10, 2, &ppipe->aent[0], 0, 0, 0, &ppipe->unk70);
}
