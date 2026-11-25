#include "attach.h"

extern "C" void *PasegAttachBase(ATTACH *attach, int *secondary)
{
    void *paseg;
    int isSecondary = 0;
    switch (attach->kind) {
    case 0:
        paseg = (attach->field_0x0C == 5) ? attach->apaseg[3] : attach->apaseg[0];
        break;
    case 1:
        paseg = attach->apaseg[1];
        break;
    case 8:
        if (attach->field_0x0C < 11) {
            if (attach->field_0x0C > 8) {
                paseg = attach->apaseg[4];
                isSecondary = 1;
            } else {
                paseg = 0;
            }
        } else {
            paseg = 0;
        }
        break;
    default:
        paseg = 0;
        break;
    }
    *secondary = isSecondary;
    return paseg;
}
