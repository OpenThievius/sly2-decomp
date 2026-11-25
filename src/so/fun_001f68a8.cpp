#include "geom.h"
#include "so.h"
extern "C" {
void func_001F68A8(SO *so, int value)
{
    for (int index = 0; index < so->cgeom; index++) {
        GEOM *geom = (GEOM *)(index * sizeof(GEOM) + (uptr)so->ageom);
        geom->grf = (geom->grf & ~(1L << 48)) | ((s64)(value & 1) << 48);
    }
}
}
