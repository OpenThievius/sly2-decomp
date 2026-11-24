#include "sly2.h"
#include "ps2inline.h"
#include "vu0inline.h"
#include "stepguard.h"
#include "goals.h"
#include "crv.h"
#include "phys.h"

/* The region link a solid object's PHYS points at (PHYS::plink): only the part func_001BD718's caller reads. */
struct LINK {
    u8 unknown_0x0[0x10];
    /* 0x10 */ s32 id;         /* GoalFollowCrv_Update passes it as the second argument */
    u8 unknown_0x14[0xC];
    /* 0x20 */ u8 region[1];   /* GoalFollowCrv_Update passes its address as the third argument */
};

/* The curve family object GoalFollowCrv_Update follows (a CRV subclass, 0x1D8 and up: the class table has CRV children of 0x1C0 to 0x1F0). */
struct CRVBUSY : CRV {
    u8 unknown_0x180[0x58];
    /* 0x1D8 */ s32 busy;      /* GoalFollowCrv_Update: while set the goal does not follow it */
};

/* GoalFollowCrv with its slot 15 (GoalFollowCrv_SetState). */
struct GOALFOLLOWCRVSTATE : GOALFOLLOWCRV {
    virtual void SetState(int state);
};

extern "C" {
void FindCrvClosestPointAll(CRV *, QW, void *, int, int, int, float *);
void GoalFollowCrv_Steer(GOALFOLLOWCRVSTATE *);
QW PosLoWorld(void *);
float SDiffCrv(CRV *, float, float);
unsigned func_001BD718(QW, int, void *, CRV *, float, int, CRV **, float *);
void func_001EEF98();
extern char B_003DD020[];
void GoalFollowCrv_Update(GOALFOLLOWCRVSTATE *self) {
    float closest;
    QW pos;
    func_001EEF98();
    GoalFollowCrv_Steer(self);
    pos = PosLoWorld(self->pstep);
    unsigned old;
    do {
        old = self->state;
        switch (old) {
        case 0:
        case 2:
        case 3: {
            if (self->field_0x40 == 0) {
                PHYS *pphys = GOAL_GUARD(self)->pphys;
                LINK *plink = 0;
                if (pphys != 0) plink = pphys->plink;
                int id = 0;
                if (plink != 0) id = plink->id;
                unsigned result = func_001BD718(pos, id, GOAL_GUARD(self)->pphys->plink->region, self->pcrv, self->s, self->reverse == 0, &self->pcrvLast, &self->diff);
                self->result = result;
                switch (result) {
                case 0:
                    break;
                case 3:
                case 4:
                    self->SetState(3);
                    break;
                case 1:
                case 2:
                    FindCrvClosestPointAll(self->pcrvLast, pos, B_003DD020, 0, 0, 0, &closest);
                    if (__builtin_fabsf(SDiffCrv(self->pcrvLast, closest, self->diff)) > 80.0f) {
                        self->hint = closest;
                        self->SetState(1);
                        break;
                    }
                    self->result = 0;
                    break;
                }
            }
            if (self->result == 0) {
                float limit;
                if (self->state == 0)
                    limit = self->nearDist;
                else
                    limit = self->farDist;
                float dist = LaneX(SqrtX(SquaredLengthXy(VectorSub(pos, self->posGoal))));
                int farther = limit < dist;
                if (farther != 0)
                    self->SetState(0);
                else
                    self->SetState(2);
            }
            break;
        }
        case 1:
        case 4: {
            CRVBUSY *crv = (CRVBUSY *)self->pcrvLast;
            if (((int)(crv->grfo >> 60) & 1) == 0 || crv->busy != 0) {
                self->SetState(0);
            } else {
                if (__builtin_fabsf(SDiffCrv(crv, self->hint, self->diff)) < 80.0f) {
                    self->SetState(0);
                } else {
                    float limit;
                    if (self->state == 1)
                        limit = self->nearDist;
                    else
                        limit = self->farDist;
                    float dist = LaneX(SqrtX(SquaredLengthXy(VectorSub(pos, self->posGoal))));
                    int farther = limit < dist;
                    if (farther != 0)
                        self->SetState(1);
                    else
                        self->SetState(4);
                }
            }
            break;
        }
        }
    } while (self->state != old);
}
}
