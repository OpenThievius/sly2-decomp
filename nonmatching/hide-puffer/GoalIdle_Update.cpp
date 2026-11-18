#include "sly2.h"
struct GOAL_IDLE {
    char pad0[0x10];
    int guard;
    char pad1[0x18 - 0x14];
    int script;
    char pad2[0x30 - 0x1C];
    float timer30;
    float value34;
    int state;
    char pad3[0x40 - 0x3C];
    int pause40;
};
extern "C" {
int FGuardScriptDone(int);
void GoalIdle_SetState(GOAL_IDLE *, int);
void func_001EEF98(void);
int func_001EF0A8(void);
int func_00209098(int);
extern float g_2dded0;
void GoalIdle_Update(GOAL_IDLE *self)
{
    func_001EEF98();
    int canAlert = func_00209098(self->guard);
    while (func_001EF0A8() == 0) {
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
            } else if (!(g_2dded0 > self->timer30)) {
                if (FGuardScriptDone(self->script) != 0) {
                    self->pause40 = 0;
                    GoalIdle_SetState(self, 2);
                }
            } else {
                GoalIdle_SetState(self, 1);
            }
            break;
        case 3:
            if (canAlert == 0) {
                if (self->pause40 != 0) {
                    GoalIdle_SetState(self, 1);
                } else {
                    GoalIdle_SetState(self, 2);
                }
            }
            break;
        }
        if (self->state == previousState)
            break;
    }
}
}
