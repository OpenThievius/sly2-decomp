#include "sly2.h"
struct Jt { u8 unknown_0x0[0x1100]; int held; };
void SetJtLookTarget();
void SetJtLookTargetHeld(Jt *self)
{
    SetJtLookTarget();
    self->held = 1;
}
