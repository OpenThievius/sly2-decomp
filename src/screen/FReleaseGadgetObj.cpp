#include "gadgetobj.h"
extern "C" {
int FReleaseGadgetObj(GADGETOBJ *gadget) {
    int state = gadget->state;
    if (state < 3) {
        if (state > 0) {
            gadget->SetState(3);
        }
    }
    return 1;
}
}
