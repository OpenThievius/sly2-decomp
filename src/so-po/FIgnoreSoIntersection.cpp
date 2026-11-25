#include "so.h"
extern "C" int FIgnoreSoIntersection(SO *a, SO *b)
{
    if ((a->grfso & 0x4000000) != 0 || a->FIsLocked() != 0) {
        if (b->FIsLocked() != 0) return 1;
    }
    return 0;
}
