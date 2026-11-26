#include "types.h"
#include "pzo_hide.h"
extern "C" {
void PostLoLoad();
void SetTnTnsOverride(s32, s32);
extern f32 RO_002BE8C0;
void AttachCyl_PostLoad(ATTACHCYL* attach) {
    PostLoLoad();
    s32 overrideTransform = attach->member.field_0x0;
    if (overrideTransform != 0) {
        SetTnTnsOverride(overrideTransform, 0);
    }
    if (attach->radius == 1e10f) {
        attach->radius = attach->heightOffset + RO_002BE8C0;
    }
}
}
