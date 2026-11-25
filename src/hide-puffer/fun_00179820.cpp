#include "stepguard.h"
#include "goals.h"
extern "C" {
void GoalHit_Deactivate();
void func_00179820(GOALHIT *self) {
    GoalHit_Deactivate();
    LO *target = ((STEPGUARD *)self->pstep)->field_0xFEC;
    if (target != 0) {
        target->Remove();
    }
}
}
