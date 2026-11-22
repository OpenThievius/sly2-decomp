// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
#include "xf.h"


extern "C" float g_2dded0;
extern "C" QW g_2a2dd0;
extern "C" void UnsubscribeLoObject(LO *plo, LO *ploTarget);
extern "C" void SubscribeLoObject(LO *plo, LO *ploTarget);
extern "C" void Goal_Pop(GOAL **ppgoal);
extern "C" GOAL *func_00205438(STEPGUARD *pguard, int classId);
extern "C" void func_0020AC28(STEPGUARD *pguard, XF *paim, int pxfLookFrom, QW vecLook);
extern "C" void func_001EF038(GOALREACT *goal);
extern "C" void func_00175488(GOALREACT *goal, int state)
{
    if (state == goal->state)
        return;
    if (goal->state == 0) {
        UnsubscribeLoObject(goal->ptarget, goal->pstep);
        goal->ptarget = 0;
        func_0020AC28(GOAL_GUARD(goal), 0, 0, g_2a2dd0);
    }
    Goal_Pop(&goal->pgoalChild);
    int *statep = &goal->state;
    *statep = state;
    goal->tState = g_2dded0;
    switch (state) {
    case 0: {
        SubscribeLoObject(goal->ptarget, goal->pstep);
        GOALTRACK *look = (GOALTRACK *)func_00205438(GOAL_GUARD(goal), 0x9F);
        look->ptarget = goal->ptarget;
        look->panimref = *(ANIMREF **)&goal->pxf->posGoal;
        if (goal->pxf->pxfParent != 0) {
            MATRIX4 pose;
            void *pvPose = goal->ptarget->Slot32(&pose);
            func_0020AC28(GOAL_GUARD(goal), goal->pxf, (int)pvPose, pose.row[3]);
        }
        look->Activate();
        break;
    }
    case 1: {
        GOALANIM *react = (GOALANIM *)func_00205438(GOAL_GUARD(goal), 0x9D);
        react->sgs = 4;
        react->ptarget = goal->ptarget;
        react->Activate();
        break;
    }
    case -1:
        func_001EF038(goal);
        break;
    }
}
