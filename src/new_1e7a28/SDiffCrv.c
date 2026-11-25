#include "crv.h"
float SMaxCrv();
float SDiffCrv(struct CRV *curve, float from, float to) {
    float difference = to - from;
    float maximum;
    if (curve->closed != 0) {
        maximum = SMaxCrv();
        if ((maximum * 0.5f) < difference) {
            difference -= maximum;
        } else if (difference < (maximum * -0.5f)) {
            difference += maximum;
        }
    }
    return difference;
}
