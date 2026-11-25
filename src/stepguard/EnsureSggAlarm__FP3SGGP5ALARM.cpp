#include "types.h"
struct ALARM;
struct SGG {
    u8 unknown_0x0[0x84];
    int calarm;
    ALARM *aalarm[8];
};

void EnsureSggAlarm(SGG *psgg, ALARM *palarm)
{
    int ialarm;
    for (ialarm = 0; ialarm < psgg->calarm; ialarm++) {
        if (psgg->aalarm[ialarm] == palarm)
            return;
    }
    int calarm = psgg->calarm;
    if ((unsigned)calarm < 8) {
        psgg->aalarm[calarm] = palarm;
        psgg->calarm = calarm + 1;
    }
}
