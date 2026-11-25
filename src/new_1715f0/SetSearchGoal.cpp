#include "goal.h"
struct SEARCHER_1725E0 { u8 unknown_0x0[0x44]; GOAL *goal; int changed; };
extern "C" void SetSearchGoal(SEARCHER_1725E0 *self, GOAL *goal) {
    GOAL *old = self->goal;
    if (goal != old) {
        if (old != 0) {
            old->Slot2();
        }
        self->goal = goal;
        if (goal != 0) {
            goal->OnAdd();
        }
        self->changed = 1;
    }
}
