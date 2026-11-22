// SPDX-License-Identifier: GPL-3.0-or-later
#include "lo.h"
#include "types.h"
// A clue: an LO that takes the next serial number when it loads and removes itself when that clue was found already.
struct CLUE : LO {
    u8 unknown_0x50[0xB0];
    /* 0x100 */ s32 serial;
};
// the world's clue counter, read here only (sw.h has no word at 0x4760)
struct SWCLUECOUNT { u8 unknown_0x0[0x4760]; s32 serialCounter; };
extern SWCLUECOUNT B_003DD490;
extern "C" void PostLoLoad();
extern "C" int FClueFound(int);
extern "C" void PostClueLoad(CLUE *self)
{
    PostLoLoad();
    self->serial = B_003DD490.serialCounter++;
    if (FClueFound(self->serial) != 0)
        self->Remove();
}
