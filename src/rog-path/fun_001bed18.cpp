#include "sly2.h"
struct OBJ;
struct VT {
    u8 unknown_0x0[0x18]; short delta18; short index18; void (*fn18)(void *, int, int, int, int, int);
    u8 unknown_0x20[0x28]; short delta48; short index48; void (*fn48)(void *);
    u8 unknown_0x50[0x58]; short deltaA8; short indexA8; void (*fnA8)(void *, int);
};
struct OBJ { u8 unknown_0x0[0xC]; VT *vt; };
struct SLOT { u8 unknown_0x0[0x20]; int owner; };
struct RTALO {
    u8 unknown_0x0[0xC]; VT *vt;
    u8 unknown_0x10[0xD0]; int count; OBJ *children[4]; unsigned flags[4];
    u8 unknown_0xF8[0x24]; SLOT *slot;
};
void func_001BED18(RTALO *alo)
{
    SLOT *slot = alo->slot;
    if (slot) {
        slot->owner = 0;
        alo->slot = 0;
        for (int index = 0; index < alo->count; index++) {
            OBJ *child = alo->children[index];
            if (alo->flags[index] & 1)
                child->vt->fn48((char *)child + child->vt->delta48);
            if (alo->flags[index] & 2)
                child->vt->fnA8((char *)child + child->vt->deltaA8, 1);
        }
        alo->vt->fnA8((char *)alo + alo->vt->deltaA8, 0);
        alo->vt->fn18((char *)alo + alo->vt->delta18, 3, 0, 0, 0, 0);
    }
}
