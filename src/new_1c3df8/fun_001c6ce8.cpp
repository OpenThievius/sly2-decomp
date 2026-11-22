// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "so.h"
#include "sw.h"
// DPRIZE: a prize the world leases clones of (CpdprizeLeaseSwDprizes), a subclass of SO; classes 91 to 93 of retail's class table
// (parent 90 of 0x230 bytes) add one virtual, slot 76, which this function calls with 2 on each clone. Its size is not known.
struct DPRIZE : SO {
    virtual void Slot76(int arg);       /* 76: CpdprizeLeaseSwDprizes calls it with 2 on a fresh clone */
};
extern "C" LO *PloFindSwObject_thunk(SW *, int, int, int);
extern "C" LO *PloLeaseCloneObject(LO *, int);
extern "C" void LockLeaseOfPlo(LO *, LO *);
int func_001C6CE8(SW *sw, int cid, int count, LO **out)
{
    int made;
    if (count == 0)
        return 0;
    int oid;
    switch (cid) {
    case 0x5B:
        oid = 0x2B3;
        break;
    case 0x5D:
        oid = 0x2B4;
        break;
    default:
        return 0;
    }
    LO *templ = PloFindSwObject_thunk(sw, 5, oid, 0);
    if (templ == 0)
        return 0;
    made = 0;
    LO **slot = out;
    for (int index = 0; index < count; index++) {
        LO *lo = PloLeaseCloneObject(templ, 0);
        if (lo == 0)
            break;
        made++;
        static_cast<DPRIZE *>(lo)->Slot76(2);
        LockLeaseOfPlo(templ, lo);
        *slot = lo;
        slot++;
    }
    return made;
}
