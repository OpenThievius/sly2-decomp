#include "types.h"
struct Gadget { u8 unknown_0x0[0x98]; float xp; };
extern "C" void func_001F4FB0(void *, Gadget *);
void AdjustGadgetObjNewXp(void *obj, Gadget *gadget)
{
    func_001F4FB0(obj, gadget);
    gadget->xp = 0.25f;
}
