#include "types.h"
#include "crv.h"
struct CurveSpan {
    u8 unknown_0x0[0xC];
    CRV *owner;
    u8 unknown_0x10[0x8];
    s32 reversed;
};
extern "C" {
float SMinCrv(CRV *);
float SMaxCrv(CRV *);
}
extern "C" void bevy_player_p14_19e110(CurveSpan *span, float *range)
{
    CRV *owner = span->owner;
    if (owner->closed != 0) {
        range[0] = -3.402823466e+38f;
        range[1] = 3.402823466e+38f;
        return;
    }
    if (span->reversed != 0) {
        range[0] = SMinCrv(owner) + 35.0f;
        range[1] = SMaxCrv(span->owner) - 100.0f;
    } else {
        range[0] = SMinCrv(owner) + 100.0f;
        range[1] = SMaxCrv(span->owner) - 35.0f;
    }
}
