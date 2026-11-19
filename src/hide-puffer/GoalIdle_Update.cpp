#include "sly2.h"
#include "goal.h"
struct GOAL_IDLE : GOAL {
    float timer30;
    float value34;
    int state;
    char pad_3C[4];
    int pause40;
};
extern "C" {
int FGuardScriptDone(int);
void GoalIdle_SetState(GOAL_IDLE *, int);
int func_00209098(void *);
int func_001EF0A8(GOAL_IDLE *);
void func_001EEF98(GOAL_IDLE *);
}
extern float g_2dded0;
extern "C" void GoalIdle_Update(GOAL_IDLE *self)
{
    func_001EEF98(self);
    int canAlert = func_00209098(self->pstep);
    while (func_001EF0A8(self) == 0) {
        int previousState = self->state;
        switch (previousState) {
        case 1:
            if (canAlert == 0) {
                if (g_2dded0 > self->value34)
                    GoalIdle_SetState(self, 0);
            } else {
                GoalIdle_SetState(self, 3);
            }
            break;
        case 2:
            if (canAlert != 0)
                GoalIdle_SetState(self, 3);
            break;
        case 0:
            if (canAlert != 0) {
                GoalIdle_SetState(self, 3);
            } else if (g_2dded0 > self->timer30) {
                GoalIdle_SetState(self, 1);
            } else if (FGuardScriptDone(*(int *)((char *)self + 0x18)) != 0) {
                self->pause40 = 0;
                GoalIdle_SetState(self, 2);
            }
            break;
        case 3:
            if (canAlert == 0) {
                if (self->pause40 != 0)
                    GoalIdle_SetState(self, 1);
                else
                    GoalIdle_SetState(self, 2);
            }
            break;
        }
        if (self->state == previousState)
            break;
    }
}
