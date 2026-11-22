// SPDX-License-Identifier: GPL-3.0-or-later
#include "lo.h"
#include "so.h"
#include "sly2.h"
#include "types.h"
#include "ps2inline.h"
#include "vu0inline.h"
#include "murray.h"

struct ASEGA { char pad[0x14]; void *p14; };
extern "C" void SetMurrayState(MURRAY *, int);
extern "C" void SetMurrayAttackState(MURRAY *, int);
extern "C" QW PosLoWorld(void *);
extern "C" QW bevy_camera_follow_track_heading_weight(void *, void *, QW);

static inline int AttackStateToStart(MURRAY *pmurray, int first)
{
    ASEGA *pfade = pmurray->field_0x190C;
    if (pfade != 0) {
        void *pa = pfade->p14;
        if (pa == pmurray->field_0x17FC || pa == pmurray->field_0x1804)
            return first + 1;
        return first;
    }
    void *ploTarget = (void *)pmurray->field_0x10DC;
    if (ploTarget != 0) {
        QW posTarget = PosLoWorld(ploTarget);
        QW posSelf = PosLoWorld(pmurray);
        QW dir = VectorSub(posTarget, posSelf);
        QW local = bevy_camera_follow_track_heading_weight(0, pmurray, dir);
        float y = LaneYInGeneralRegister(local);
        if (0.0f < y)
            return first;
        return first + 1;
    }
    return first + 1;
}

void StartMurrayAttackA(MURRAY *pmurray)
{
    SetMurrayState(pmurray, 0xB);
    SetMurrayAttackState(pmurray, AttackStateToStart(pmurray, 0));
}
