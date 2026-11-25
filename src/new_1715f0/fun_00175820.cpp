#include "types.h"
struct Class_175820 { u8 unknown_0x0[0x70]; s64 flags; };
struct Obj_175820 { u8 unknown_0x0[0xEC]; Class_175820 *cls; };
struct Other_175820 { u8 unknown_0x0[4]; Obj_175820 *obj; };
struct Arg1_175820 { u8 unknown_0x0[4]; Obj_175820 *obj; u8 unknown_0x8[8]; s64 flags; };
struct Arg0_175820 { u8 unknown_0x0[0x74]; int field; };
extern "C" {
int FIsBasicDerivedFrom(Obj_175820 *, int);
int func_00175820(Arg0_175820 *self, Arg1_175820 *other) {
    if ((other->flags & (0x8000L << 33)) != 0) return 0;
    Obj_175820 *obj = other->obj;
    if ((obj->cls->flags & 4) != 0) return 0;
    if (self->field != 0 && FIsBasicDerivedFrom(obj, 0x62) != 0) return 0;
    return FIsBasicDerivedFrom(other->obj, 0x33) == 0;
}
}
