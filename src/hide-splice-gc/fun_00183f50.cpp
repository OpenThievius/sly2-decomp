#include "types.h"
#include "xfm.h"
#include "pzo_hide.h"

/* an attach point: an XFM with a MEMBER at 0xE0 (pzo_hide.h ATTACHPT) */
struct ATTACHPT_183F50 : XFM {
    MEMBER member;
};

extern "C" {
f32 PostLoLoad();
extern f32 RO_002BE900;

void func_00183F50(ATTACHPT_183F50* attach) {
    PostLoLoad();
    if (attach->member.field_0x1C == 0) {
        attach->member.field_0x1C = 7;
    }
    if (attach->field_0x38 == 1e10f) {
        attach->field_0x38 = RO_002BE900;
    }
}
}
