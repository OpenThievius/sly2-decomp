/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pad.h"
extern "C" {
s32 func_00243458(s32 port, s32 slot, s32 state);
s32 sceSifCallRpc(PADCLIENT *client, s32 command, s32 mode, void *send, s32 sendSize, void *receive, s32 receiveSize, void *endFunction, void *endData);
extern PADCLIENT B_00450580[];
extern PADREQUEST B_004507C0;
s32 scePadSetMainMode(s32 port, s32 slot, s32 argument0, s32 argument1) {
    B_004507C0.arguments.main.argument0 = argument0;
    B_004507C0.arguments.main.argument1 = argument1;
    B_004507C0.command = 6;
    B_004507C0.port = port;
    B_004507C0.slot = slot;
    if (sceSifCallRpc(B_00450580, 1, 0, &B_004507C0, 0x80, &B_004507C0, 0x80, 0, 0) < 0) {
        return 0;
    }
    if (B_004507C0.result == 1) {
        func_00243458(port, slot, 2);
    }
    return B_004507C0.result;
}
}
