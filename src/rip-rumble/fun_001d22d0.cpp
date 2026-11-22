// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "ps2inline.h"
#include "vu0inline.h"
#include "swfind.h"
#include "vehicle.h"

extern SW B_003DD490;
extern "C" {
extern const float RO_FLT_002A7810;
extern float g_2c20c0[3];
QW PosLoWorld(void *);
/* the targets it scores keep their ammunition slot at 0x158 */
struct AMMOTARGET {
    u8 unknown_0x0[0x158];
    s32 iammo;
};
LO *func_001D22D0(VEHICLE *vehicle)
{
    LO *found[16];
    LO *best = 0;
    QW posSelf = PosLoWorld(vehicle);
    int count = CploFindSwObjectsByClass(&B_003DD490, 0x105, 0x6C, 0, 0x10, found);
    float bestScore = RO_FLT_002A7810;
    for (int index = 0; index < count; index++) {
        LO *object = found[index];
        QW posObject = PosLoWorld(object);
        float distance = LaneX(SqrtX(SquaredLengthXy(VectorSub(posObject, posSelf))));
        if (object == vehicle->ploChase)
            distance = g_2c20c0[0] + distance * (g_2c20c0[1] + distance * g_2c20c0[2]);
        distance += vehicle->aammo[((AMMOTARGET *)object)->iammo].bias;
        if (distance < bestScore) {
            bestScore = distance;
            best = object;
        }
    }
    return best;
}
}
