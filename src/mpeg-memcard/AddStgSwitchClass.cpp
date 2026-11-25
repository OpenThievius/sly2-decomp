#include "stgswitch.h"
extern "C" void AddStgSwitchClass(STGSWITCH *self, int cid, int field_0x4)
{
 int count = self->cclass; if (count < 8) { STGCLASS *entry = self->aclass + count; self->cclass = count + 1; entry->cid = cid; entry->field_0x4 = field_0x4; }
}
