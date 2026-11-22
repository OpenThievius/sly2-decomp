/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
void GetOsdConfigParam(u32 *config);
s32 func_0024A820(void);
extern u8 D_002C8374;
/* The config word: bit 4 is the legacy language flag, bits 13 to 15 a revision, bits 16 to 20 the language. */
u8 sceScfGetLanguage(void) {
    u8 result;
    u32 config;
    GetOsdConfigParam(&config);
    if (func_0024A820() != 0) {
        result = D_002C8374;
        goto done;
    }
    GetOsdConfigParam(&config);
    if ((config >> 13) & 7) {
        result = (config >> 16) & 0x1F;
        goto done;
    }
    return (config >> 4) & 1;
done:
    return result;
}
}
