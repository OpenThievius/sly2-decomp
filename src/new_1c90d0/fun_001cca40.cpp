#include "sly2.h"
struct TARGET_1CCA40 { u8 unknown_0x0[0xE0]; u32 flags; };
struct SEEKER_1CCA40 { u8 unknown_0x0[0x1000]; u32 mask; };
extern char B_003DD490;
extern "C" int CploFindSwObjectsByClass(void *, int, int, int, int, TARGET_1CCA40 **);
extern "C" TARGET_1CCA40 *func_001CCA40(SEEKER_1CCA40 *seeker, int classId)
{
    TARGET_1CCA40 *found[4];
    int count = CploFindSwObjectsByClass(&B_003DD490, 0x401, 0x14, classId, 4, found);
    for (int index = 0; index < count; index++) {
        if (found[index]->flags & seeker->mask)
            return found[index];
    }
    return 0;
}
