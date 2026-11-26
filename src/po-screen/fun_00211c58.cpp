#include "blot.h"
/* the 0x130-byte blot class func_00112CD0 allocates (vtable D_002C9670, Blot_Hide and Blot_Show in its slots): its own words
   start at 0x110 (the constructor is the only reader, so a local view, not a shared class) */
struct BLOTPLAINVIEW : BLOTVIEW {
    u8 unknown_0x108[0x8];
    s32 field_0x110;
    s32 field_0x114;
    s32 field_0x118;
    s32 field_0x11C;
    s32 field_0x120;
};
extern "C" {
s32 Blot_Construct(BLOTVIEW *);
extern s32 D_002C9670;
BLOTPLAINVIEW *func_00211C58(BLOTPLAINVIEW *arg0) {
    Blot_Construct(arg0);
    arg0->field_0x110 = -1;
    arg0->vtable = &D_002C9670;
    arg0->field_0x114 = -1;
    arg0->field_0x118 = -1;
    arg0->field_0x11C = -1;
    arg0->field_0x120 = -1;
    return arg0;
}
}
