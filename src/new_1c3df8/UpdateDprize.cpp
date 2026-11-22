// SPDX-License-Identifier: GPL-3.0-or-later
#include "vu0inline.h"
#include "dprize.h"
#include "clock.h"
#include "ps2inline.h"

extern "C" {
void UpdateSo(DPRIZE *, float);
void func_001C6308(DPRIZE *);
void CheckDprizeBounce(DPRIZE *);
void CheckDprizeCollect(DPRIZE *);
extern float D_002C0D50;
}

void UpdateDprize(DPRIZE *pdprize, float dt)
{
    UpdateSo(pdprize, dt);
    func_001C6308(pdprize);
    switch (pdprize->dprizes) {
    case 0:
        if (LaneX(SquaredLength(*(QW *)&pdprize->velocity)) > 10000.0f)
            CheckDprizeBounce(pdprize);
    case 5:
        CheckDprizeCollect(pdprize);
        return;
    case 3:
        if (pdprize->velocity.z < 0.0f)
            pdprize->SetDprizes(4);
        return;
    case 4:
        if (pdprize->landing != 0 && pdprize->velocity.z < 25.0f) {
            pdprize->landing = 0;
            pdprize->SetDprizes(0);
        } else if (D_002C0D50 < g_2dded0.t - pdprize->tDprizes) {
            pdprize->SetDprizes(2);
        } else {
            CheckDprizeBounce(pdprize);
            CheckDprizeCollect(pdprize);
        }
        return;
    case 1:
    case 2:
    case 6:
    default:
        return;
    }
}
