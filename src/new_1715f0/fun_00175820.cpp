#include "types.h"
#include "oxa.h"
#include "geom.h"
#include "so.h"
/* the filter's first argument, read only here: a local view */
struct Arg0_175820 { u8 unknown_0x0[0x74]; int field; };
extern "C" {
int FIsBasicDerivedFrom(void *, int);
int func_00175820(Arg0_175820 *self, GEOM *other) {
    if ((other->grf & (0x8000L << 33)) != 0) return 0;
    SO *obj = other->pso;
    if ((obj->poxa->grf & 4) != 0) return 0;
    if (self->field != 0 && FIsBasicDerivedFrom(obj, 0x62) != 0) return 0;
    return FIsBasicDerivedFrom(other->pso, 0x33) == 0;
}
}
