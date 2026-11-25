// SPDX-License-Identifier: GPL-3.0-or-later
#include "globset.h"
// The class declares Virtual0 itself (no inline body): it becomes the key function, so gcc leaves the vtable external instead of emitting its own copy.
// new() factory of a class with two bases. The primary chain: a base with three words (the first two zeroed) and its
// vptr at +0xC, then a class holding the globset at +0x80 (its vptr, retail D_002D9978, is stored before the globset
// constructor runs). The second base sits at +0x164 with its vptr at +0x170. The derived class's inline constructor
// then stores its two vtables (retail D_002D20D0 at +0xC, D_002D2090 at +0x170).
// Link: gcc names the vtables _vt$16CRefHolder112100, _vt$13CObject112100 and _vt$13CObject112100$16CSecondary112100.
struct CBase112100 {
    int unk0x0;
    int unk0x4;
    int unk0x8;
    CBase112100() { unk0x0 = 0; unk0x4 = 0; }
    virtual void Virtual0();
};
struct CRefHolder112100 : CBase112100 {
    u8 unknown_0x10[0x70];
    GLOBSET globset;
    u8 unknown_0xD0[0x94];
    virtual void Virtual0();
};
struct CSecondary112100 {
    int unk0x0[3];
    virtual void Virtual0();
};
struct CObject112100 : CRefHolder112100, CSecondary112100 {
    u8 unknown_0x174[0x1A0 - 0x174];
    virtual void Virtual0();
};
void *func_00112100(void)
{
    return new CObject112100;
}
