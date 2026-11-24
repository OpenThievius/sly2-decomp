#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
#include "clock.h"
extern "C" {
float GRandInRange(float, float);
void Goal_Pop(GOAL **);
QW PosLoWorld(void *);
PATHZONE *PpathzoneFindPos(QW, int);
void SetAlertState(ALERT *, int);
void SetGoalTarget(GOALGOTO *, GOALTARGET *);
void func_00154038(void *, void *, int);
GOAL *func_00205438(STEPGUARD *, int);
void func_00208540(void *, int);
void func_002562A8(void *);
void GoalNotice_SetState(GOALNOTICE *self, unsigned state) {
    GOALTARGET target;
    if (state != self->state) {
        Goal_Pop(&self->pgoalChild);
        if (self->state == 1) {
            GOALREACTRANGE *range = self->prange;
            float now = g_2dded0.t;
            GOAL_GUARD(self)->tCooldown = now + GRandInRange(range->lo, range->hi);
            self->prange = 0;
        }
        self->state = state;
        self->tState = g_2dded0.t;
        switch (state) {
        case 0: {
            GOAL *obj = func_00205438(GOAL_GUARD(self), 0xB3);
            obj->Activate();
            return;
        }
        case 1: {
            GOALREACT *obj = (GOALREACT *)func_00205438(GOAL_GUARD(self), 0xA4);
            obj->ptarget = self->ptarget;
            *(GOALREACTRANGE **)((char *)obj + 0x3C) = self->prange; /* GOALREACT::pxf is at 0x3C: this goal keeps a range there */
            GOAL_GUARD(self)->tCooldown = 3.4028235e38f;
            obj->Activate();
            SetAlertState(GOAL_GUARD(self)->palert, 3);
            return;
        }
        case 2: {
            GOALANIM *obj = (GOALANIM *)func_00205438(GOAL_GUARD(self), 0xAD);
            obj->ptarget = self->ptarget;
            obj->Activate();
            SetAlertState(GOAL_GUARD(self)->palert, 4);
            return;
        }
        case 3: {
            GOALGOTO *obj = (GOALGOTO *)func_00205438(GOAL_GUARD(self), 0xBA);
            obj->fLink = 1;
            obj->field_0x38 = 0x1C;
            QW posA = PosLoWorld(self->ptarget);
            QW posB = PosLoWorld(self->ptarget);
            func_002562A8(&target);
            target.pos = posB;
            SetGoalTarget(obj, &target);
            obj->ptarget = self->ptarget;
            obj->field_0xAC = 1;
            obj->Activate();
            self->posLast = posA;
            self->pzone = PpathzoneFindPos(posA, 1);
            return;
        }
        case 4: {
            GOALANIM *obj = (GOALANIM *)func_00205438(GOAL_GUARD(self), 0x9D);
            obj->sgs = 0xD;
            obj->Activate();
            func_00154038(GOAL_GUARD(self)->psensor, self->ptarget, 0);
            func_00208540(GOAL_GUARD(self), 0);
            return;
        }
        case 5: {
            GOALANIM *obj = (GOALANIM *)func_00205438(GOAL_GUARD(self), 0x9E);
            obj->sgs = 1;
            obj->Activate();
            break;
        }
        }
    }
}
}
