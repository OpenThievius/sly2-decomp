/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
/* a request: its three trailing arguments sit at 0x24 */
struct REQUEST_236E30 {
    u8 unknown_0x0[0x24];
    s32 argument0;
    s32 argument1;
    s32 argument2;
};
extern int func_0023AFE8(unsigned int, void *, int, int, int, int);
s32 func_00236E30(void *unused_first, void *unused_second, void *unused_third, REQUEST_236E30 *request) {
    return (func_0023AFE8(0x80000008, request, 0x40, request->argument0, request->argument1, request->argument2) != 0) ? 0 : 0x800;
}
}
