#include "acr.h"
extern "C" int func_0012BB70(ACRBL *pacrb, float time) {
    int last = pacrb->ckey - 1;
    int index;
    for (index = 1; index < last; index++) {
        if (time < pacrb->akey[index].t)
            break;
    }
    return index;
}
