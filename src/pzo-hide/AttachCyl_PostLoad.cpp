#include "types.h"

struct AttachCyl {
    u8 unknown_0x0[0x38];
    f32 radius;
    u8 unknown_0x3C[0xE0 - 0x3C];
    s32 transformOverride;
    u8 unknown_0xE4[0x10C - 0xE4];
    f32 cylinderRadius;
};

extern "C" {
void PostLoLoad();
void SetTnTnsOverride(s32, s32);
extern f32 RO_002BE8C0;

void AttachCyl_PostLoad(AttachCyl* attach) {
    PostLoLoad();
    s32 overrideTransform = attach->transformOverride;
    if (overrideTransform != 0) {
        SetTnTnsOverride(overrideTransform, 0);
    }
    if (attach->radius == 1e10f) {
        attach->radius = attach->cylinderRadius + RO_002BE8C0;
    }
}
}
