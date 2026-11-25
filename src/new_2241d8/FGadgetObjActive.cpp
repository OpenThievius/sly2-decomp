#include "sly2.h"
#include "gadgetobj.h"
extern "C" int FGadgetObjActive(GADGETOBJ *pgadget)
{
    int state = pgadget->state;
    if (state < 3) {
        if (state > 0)
            return 1;
    }
    return 0;
}
