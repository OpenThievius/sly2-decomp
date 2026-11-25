#include "types.h"
/* a goal's state word at 0x4C and a float at 0xE0 (the layout of GoalFollowCrvAnim, goals.h; the class of this caller is a guess, so a view) */
struct GOAL_1792E8 {
    u8 unknown_0x0[0x4C];
    /* 0x4C */ int state;
    u8 unknown_0x50[0xE0 - 0x50];
    /* 0xE0 */ float t;
};
extern "C" int func_001792E8(GOAL_1792E8 *arg0)
{
    int state = arg0->state;
    int result = 0;
    if (state < 2) {
        if (state >= 0) {
            result = 1;
            if (arg0->t < 0.0f)
                ; else
                result = 0;
        }
    }
    return result;
}
