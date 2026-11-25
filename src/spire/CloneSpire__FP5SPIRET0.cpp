#include "spire.h"
extern "C" void CloneXfm(SPIRE *, SPIRE *);
extern "C" void CloneSpire__FP5SPIRET0(SPIRE *self, SPIRE *other)
{
    DLE saved = self->dle;
    CloneXfm(self, other);
    self->dle = saved;
}
