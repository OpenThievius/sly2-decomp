#include "cplcy.h"
extern "C" void ActivateCplcy(CPPOLICY *, int, CPHOLDER *);
extern "C" void bevy_camera_policy_activate(CPPOLICY *self, int unused, CPHOLDER *holder)
{
    ActivateCplcy(self, unused, holder);
    self->holder = holder;
    CPOBJECT *object = holder->object;
    CPVTABLE *vtable = object->vtable;
    vtable->fn_0xC((char *)object + vtable->delta_0x8);
}
