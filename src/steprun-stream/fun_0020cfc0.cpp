#include "types.h"
extern "C" {
int FFilterHitTestDefault(int, void *);
int FIsBasicDerivedFrom(void *, int);
struct Hit_20CFC0 { u8 unknown_0x0[4]; void *obj; u8 unknown_0x8[8]; s64 grf; };
int func_0020CFC0(int arg0, Hit_20CFC0 *arg1) {
    if ((arg1->grf & (0x8000L << 0x21)) != 0 && FIsBasicDerivedFrom(arg1->obj, 0x59) != 0)
        return 1;
    return FFilterHitTestDefault(arg0, arg1);
}
}
