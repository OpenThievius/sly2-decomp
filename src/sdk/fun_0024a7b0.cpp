/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
s32 func_00237EA8(const char *path, s32 mode);
s32 sceRead(s32 fd, void *buffer, s32 size);
s32 sceClose(s32 fd);
extern char D_002C8378[0xE];
extern const char RO_002AC270[];
/* Reads the 14-byte ROM version file once and returns the cached copy. */
char *func_0024A7B0(void) {
    s32 fd;
    if (D_002C8378[0] == 0) {
        fd = func_00237EA8(RO_002AC270, 1);
        if (fd >= 0) {
            sceRead(fd, D_002C8378, 0xE);
            sceClose(fd);
        }
    }
    return D_002C8378;
}
}
