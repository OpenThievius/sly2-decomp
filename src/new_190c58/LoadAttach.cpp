// SPDX-License-Identifier: GPL-3.0-or-later
#include "attach.h"
extern "C" LO *PloNew(int cid, SO *paloParent, int oid, int isplice);
extern "C" void SetTnTnsOverride(TN *ptn, int value);
extern "C" void ResetJtDynamicTunnel__FP2JT(JT *);
extern "C" void BuildPlainBlend(SLY *pjt, u8 *pblend, QW *pvec);
extern "C" void PostStepLoadRun__FP4STEPP5BLRUNPP6ASEGBL(u8 *prun);
extern "C" void EnsureAsegBlendDynamic(SLY *pjt, int, int, u8 *pasegblA, int, int, int, u8 *pasegblB);
extern "C" void func_001CC5E8(u8 *pcarry, SLY *pjt, void **ppvField);

void LoadAttach(ATTACH *attach)
{
    TN *tn = (TN *)PloNew(0xF, 0, 0x148, -1);
    attach->ptn = tn;
    SetTnTnsOverride(tn, 0);
    ResetJtDynamicTunnel__FP2JT((JT *)attach);
    BuildPlainBlend(attach->pjt, attach->blendA, &attach->vecBlendA);
    BuildPlainBlend(attach->pjt, attach->blendB, &attach->vecBlendB);
    PostStepLoadRun__FP4STEPP5BLRUNPP6ASEGBL(attach->runA);
    PostStepLoadRun__FP4STEPP5BLRUNPP6ASEGBL(attach->runB);
    EnsureAsegBlendDynamic(attach->pjt, 0xC, 3, attach->asegblA, 0, 0, 0, attach->asegblB);
    SLY *pjt = attach->pjt;
    func_001CC5E8(attach->carry, pjt, &pjt->field_0x1030);
}
