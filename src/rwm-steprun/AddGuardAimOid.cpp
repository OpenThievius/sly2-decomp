#include "types.h"
struct Owner {
    u8 unknown_0x0[0xEB8];
    int items[8];
    unsigned count;
};
void AddGuardAimOid(Owner *owner, int oid)
{
    if (oid != -1) {
        unsigned count = owner->count;
        if (count < 8) {
            owner->items[count] = oid;
            owner->count = count + 1;
        }
    }
}
