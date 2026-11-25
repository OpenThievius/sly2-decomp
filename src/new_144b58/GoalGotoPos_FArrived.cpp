#include "goals.h"
extern "C" {
int GoalFollowCrv_FAtEnd(GOALFOLLOWCRV *);
int GoalGotoPos_FArrived(GOAL *self) {
    int result = 0;
    GOALFOLLOWCRV *crv = (GOALFOLLOWCRV *)self->pgoalChild;
    if (GoalFollowCrv_FAtEnd(crv) || crv->state == 2) result = 1;
    return result;
}
}
