#include "types.h"
extern "C" u64 GrfsgsFromSgs(int sgs)
{
    if (sgs == -1)
        return 0;
    return 1UL << sgs;
}
