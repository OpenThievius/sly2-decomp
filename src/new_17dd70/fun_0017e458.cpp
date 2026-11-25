// SPDX-License-Identifier: GPL-3.0-or-later
#include "phys.h"
#include "step.h"
#include "goals.h"
#include "pathzone.h"
struct LINK { u8 unknown_0x0[0x10]; PATHZONE *zone; };
extern "C" {
void func_001EEF98();
int func_0017E570(GOALFOLLOWROUTE *);
int func_0017EAE8(void *);
int func_0017E5F0(GOALFOLLOWROUTE *);
void func_0017E580(GOALFOLLOWROUTE *);
void func_0017E6B0(GOALFOLLOWROUTE *, int);
int FGoalAnimDone(void *, ROUTE *);
int GoalFollowCrv_FAtEnd(void *, ROUTE *);
}
extern float g_2dded0;
extern "C" void func_0017E458(GOALFOLLOWROUTE *pgoal)
{
    ROUTE *proute;
    PHYS *pphys;
    LINK *plink;
    PATHZONE *zone;
    func_001EEF98();
    if (func_0017E570(pgoal))
        return;
    switch (pgoal->state) {
    case 1:
        if (func_0017EAE8(((void *)pgoal->pgoalChild)) == 0)
            break;
        goto next;
    case 0: {
        proute = pgoal->proute;
        switch (proute->kind) {
        case 1:
            if (FGoalAnimDone(((void *)pgoal->pgoalChild), proute)) {
                if (func_0017E5F0(pgoal)) {
                next:
                    func_0017E580(pgoal);
                    return;
                }
                goto enter;
            }
            break;
        case 0: {
            if (pgoal->tEnd < g_2dded0) {
            enter:
                func_0017E6B0(pgoal, 1);
                return;
            }
            pphys = pgoal->pstep->pphys;
            plink = 0;
            if (pphys)
                plink = pphys->plink;
            zone = 0;
            if (plink)
                zone = plink->zone;
            if (zone == proute->ppathzone) {
                if (GoalFollowCrv_FAtEnd(((void *)pgoal->pgoalChild), proute))
                    func_0017E580(pgoal);
            }
            break;
        }
        }
        break;
    }
    }
}
