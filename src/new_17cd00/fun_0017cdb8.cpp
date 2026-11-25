#include "types.h"
struct Owner_17CDB8 { u8 unknown_0x0[0xF84]; int curve; float limit; int flag; };
struct Obj_17CDB8 { u8 unknown_0x0[0x10]; Owner_17CDB8 *owner; u8 unknown_0x14[0x28]; float value; };
extern "C" {
float SMaxCrv(int);
float SMinCrv(int);
void func_0017CD00(Obj_17CDB8 *, int);
void func_0017CDB8(Obj_17CDB8 *obj, int useMax) {
    int curve = obj->owner->curve;
    if (useMax != 0) {
        obj->value = SMaxCrv(curve);
    } else {
        obj->value = SMinCrv(curve);
    }
    Owner_17CDB8 *owner = obj->owner;
    owner->flag = owner->limit < obj->value;
    func_0017CD00(obj, 0);
}
}
