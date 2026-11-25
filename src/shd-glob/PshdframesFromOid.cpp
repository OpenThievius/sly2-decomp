#include "sly2.h"
#include "shdframes.h"
extern "C" {
extern SHDFRAMES *B_003E1590;
SHDFRAMES *PshdframesFromOid(int oid)
{
    char frame[0x10] __attribute__((aligned(16))); // retail frame shows a dead 0x10 area
    if (oid == -1) return 0;
    SHDFRAMES *cursor = B_003E1590;
    while (cursor) {
        if (cursor->oid == oid) return cursor;
        cursor = cursor->next;
    }
    return 0;
}
}
