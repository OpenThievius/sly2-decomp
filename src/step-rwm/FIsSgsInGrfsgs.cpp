#include "types.h"
extern "C" s64 GrfsgsFromSgs(int);
int FIsSgsInGrfsgs(s64 grfsgs, int sgs)
{
    int result = (grfsgs & GrfsgsFromSgs(sgs)) != 0;
    return result;
}
