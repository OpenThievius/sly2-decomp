#include "sly2.h"
#include "gadgetobj.h"
extern "C" int FGadgetObjKept(GADGETOBJ *pgadget)
{
 int gadget = pgadget->gadget;
 if (gadget != 7 && gadget != 0xb) return 0; return 1;
}
