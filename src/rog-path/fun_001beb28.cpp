#include "sly2.h"
struct VT {
    u8 unknown_0x0[0x18]; short delta18; short index18; void (*fn18)(void *, int, int, int, int, int);
    u8 unknown_0x20[0x20]; short delta40; short index40; void (*fn40)(void *);
    short delta48; short index48; void (*fn48)(void *);
    u8 unknown_0x50[0x58]; short deltaA8; short indexA8; void (*fnA8)(void *, int);
    u8 unknown_0xB0[0x8]; short deltaB8; short indexB8; void (*fnB8)(void *);
};
struct ROOT { u8 unknown_0x0[0xC]; VT *vt; };
struct OBJ { u8 unknown_0x0[0xC]; VT *vt; u8 unknown_0x10[0x4]; ROOT *root; u8 unknown_0x18[0x10]; u64 grf; u8 unknown_0x30[0x10]; unsigned *pgrf; };
struct SLOT { u8 unknown_0x0[0x20]; void *owner; u8 unknown_0x24[0x4]; };
struct RTALO {
    u8 unknown_0x0[0xC]; VT *vt;
    u8 unknown_0x10[0xD0]; int count; OBJ *children[4]; unsigned flags[4];
    u8 unknown_0xF8[0x24]; SLOT *slot;
};
extern "C" {
extern SLOT B_003E1A78[];
extern char B_003DD4BC[];
int FIsLoInWorld(void *);
void AppendDlEntry(void *, void *);
}
SLOT *func_001BEB28(RTALO *alo)
{
    if (alo->slot == 0) {
        for (unsigned slotIndex = 0; slotIndex < 2; slotIndex++) {
            SLOT *candidate = (SLOT *)((char *)B_003E1A78 + slotIndex * 0x28);
            if (candidate->owner == 0) {
                alo->slot = candidate;
                break;
            }
        }
        if (alo->slot != 0) {
            alo->slot->owner = alo;
            for (int index = 0; index < alo->count; index++) {
                unsigned *pflag = &alo->flags[index];
                OBJ *child = *(OBJ **)((char *)pflag - 0x10);
                *pflag = 0;
                if (((child->grf >> 60) & 1) == 0) {
                    *pflag = 1;
                    child->vt->fn40((char *)child + child->vt->delta40);
                    if (FIsLoInWorld(child) == 0) {
                        AppendDlEntry(B_003DD4BC, child->root);
                        ROOT *inner = *(ROOT **)child->root;
                        inner->vt->fnB8((char *)inner + inner->vt->deltaB8);
                    }
                }
                unsigned flags = (uptr)child->pgrf;
                if (((flags ^ 1) & 1) != 0)
                    flags = *child->pgrf;
                if ((flags & 8) != 0) {
                    *pflag |= 2;
                    child->vt->fnA8((char *)child + child->vt->deltaA8, 0);
                }
            }
            alo->vt->fnA8((char *)alo + alo->vt->deltaA8, 1);
            alo->vt->fn18((char *)alo + alo->vt->delta18, 2, 0, 0, 0, 0);
        }
    }
    return alo->slot;
}
