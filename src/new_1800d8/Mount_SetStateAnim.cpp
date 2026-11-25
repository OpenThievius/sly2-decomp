#include "mount.h"
void Mount_SetStateAnim(MOUNT *pmount, unsigned index, int first, int second)
{
    if (index < 5)
    {
        pmount->aentry[index].oid = first;
        pmount->aentry[index].flags = second;
    }
}
