#include "sly2.h"
/* the laser as func_001DE2D8 reads it: an oid filter and a class filter after the SO (laser.h leaves them undeclared: one reader) */
struct LASER { u8 unknown_0x0[0x150]; int coid; int aoid[7]; int ccls; int acls[7]; };
extern "C" int FLoHasOid(void *, int);
extern "C" int FIsBasicDerivedFrom(void *, int);
extern "C" int IMax(int, int);

int func_001DE2D8(LASER *plaser, void *pobject)
{
    int result = 1;
    for (int index = 0; index < plaser->coid; index++) {
        if (FLoHasOid(pobject, plaser->aoid[index]))
            result = IMax(result, 2);
    }
    for (int index = 0; index < plaser->ccls; index++) {
        if (FIsBasicDerivedFrom(pobject, plaser->acls[index]))
            result = IMax(result, 2);
    }
    return result;
}
