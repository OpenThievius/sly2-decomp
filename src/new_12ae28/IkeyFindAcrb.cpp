#include "acr.h"
extern "C" int IkeyFindAcrb(ACRB *pacrb, float time) {
    int last = pacrb->ckey - 1;
    int index;
    for (index = 1; index < last; index++) {
        if (time < pacrb->akey[index].t)
            break;
    }
    return index;
}
