// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
/* The globset an SO embeds at 0x80 (so.h field_0x80): its constructor is all that is known; it sets the word at 0x4C to -1. */
struct GLOBSET {
    u8 unknown_0x0[0x4C];
    /* 0x4C */ s32 field_0x4C; /* GLOBSET::GLOBSET sets it to -1 */
    GLOBSET();
};
GLOBSET::GLOBSET()
{
    field_0x4C = -1;
}
