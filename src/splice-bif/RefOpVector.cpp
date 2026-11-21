// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
struct CPair { int cref; int pad4; CRef ref; CPair *next; };
struct CFrame;
extern "C" CRef CRef_RefCoerceF32(CRef *pref);
extern "C" CRef RefOpVector(int carg, CRef *aref, CFrame *pframe)
{
    CRef refVector;
    refVector.SetTag(TAGK_Vector);
    float *pvec = (float *)refVector.m_tag.m_pvector;
    CPair *ppair;
    if (carg > 0) ppair = (CPair *)aref[0].m_tag.m_n;
    switch (carg) {
    case 0:
        pvec[2] = 0.0f;
        pvec[1] = 0.0f;
        pvec[0] = 0.0f;
        break;
    case 1: {
        CRef refTemp = CRef_RefCoerceF32(&ppair->ref);
        float g = refTemp.m_tag.m_g;
        pvec[2] = g;
        pvec[1] = g;
        pvec[0] = g;
        break;
    }
    case 3: {
        for (int index = 0; index < 3; index++) {
            CRef refTemp = CRef_RefCoerceF32(&ppair->ref);
            pvec[index] = refTemp.m_tag.m_g;
            ppair = ppair->next;
        }
        break;
    }
    }
    return refVector;
}
