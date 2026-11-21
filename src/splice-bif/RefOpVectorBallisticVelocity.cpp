// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
struct CPair { int cref; int pad4; CRef ref; CPair *next; };
#include "phys.h"
#include "so.h"
struct CFrame;
extern "C" {
void CRef_RefCoerceF32(CRef *, CRef *);
QW FCalculateMuzzleVelocity__FP6VECTORT0fT0P2SO(QW, QW, float, QW);
}
static inline QW *PvSetTag_122BE0(CRef *pref, TAGK tagk)
{
    pref->SetTag(tagk);
    return (QW *)pref->m_tag.m_pvector;
}
extern "C" CRef RefOpVectorBallisticVelocity(int carg, CRef *aref, CFrame *pframe)
{
    VECTOR accel;
    accel.x = 0.0f;
    accel.z = -1750.0f;
    accel.y = 0.0f;
    if (aref[3].m_tagk != 0) {
        SO *pso = (SO *)((CPair *)aref[3].m_tag.m_n)->ref.m_tag.m_n;
        if (pso != 0) {
            if (pso->pphys != 0) {
                *(QW *)&accel = pso->pphys->dvGravity;
            }
        }
    }
    CRef refVelocity;
    QW *pvelocity = PvSetTag_122BE0(&refVelocity, TAGK_Vector);
    QW accelValue = *(QW *)&accel;
    QW posFrom = *(QW *)aref[0].m_tag.m_pvector;
    QW posTo = *(QW *)aref[1].m_tag.m_pvector;
    {
        CRef refTemp;
        CRef_RefCoerceF32(&refTemp, &aref[2]);
        *pvelocity = FCalculateMuzzleVelocity__FP6VECTORT0fT0P2SO(posFrom, posTo, refTemp.m_tag.m_g, accelValue);
    }
    return refVelocity;
}
