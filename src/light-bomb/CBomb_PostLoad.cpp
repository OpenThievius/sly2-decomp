#include "alloc.h"
/* the bomb: AddBombCustomXps reads the same three words (0x1F4 the custom-xp flag, 0x1FC the allocated xp array) */
struct BOMB {
    u8 unknown_0x0[0x1F4];
    /* 0x1F4 */ s32 fCustom;
    /* 0x1F8 */ s32 cXp;
    /* 0x1FC */ void *axp;
};
extern "C" {
void PostSoLoad();
void *PvAllocSwImpl__Fi(ALLOCREQ *);

void CBomb_PostLoad(BOMB *bomb)
{
    ALLOCREQ req __attribute__((aligned(16)));

    PostSoLoad();
    if (bomb->fCustom != 0) {
        req.cb = 0xC0;
        req.cbAlign = 0x10;
        bomb->axp = PvAllocSwImpl__Fi(&req);
    }
}
}
