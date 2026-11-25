#include "types.h"
struct Object { u8 unknown_0x0[0x34]; float field34; int field38; float field3C; };
void func_001EEF68();
void func_00144E20(struct Object *object) {
    func_001EEF68();
    object->field34 = 40.0f;
    object->field38 = 1;
    object->field3C = 1.0f;
}
