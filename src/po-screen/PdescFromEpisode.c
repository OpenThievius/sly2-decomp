/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct EPISODEDESC {
    u8 unknown_0x0[0x4];
    s32 field_0x4;
    u8 unknown_0x8[0x34];
    s32 field_0x3C;
};
extern struct EPISODEDESC *B_003E1C50;

struct EPISODEDESC *PdescFromEpisode(s32 episode) {
    struct EPISODEDESC *pdesc;
    s32 valid;

    if (episode == -1) {
        return 0;
    }
    pdesc = B_003E1C50 + episode;
    valid = 0;
    if (pdesc != 0) {
        valid = pdesc->field_0x4 != pdesc->field_0x3C;
    }
    return (valid == 0) ? 0 : pdesc;
}
