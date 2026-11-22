/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pad.h"
extern "C" {
s32 func_00243458(s32 port, s32 slot, s32 state);
s32 sceSifCallRpc(PADCLIENT *client, s32 command, s32 mode, void *send, s32 sendSize, void *receive, s32 receiveSize, void *endFunction, void *endData);
extern PADCLIENT B_00450580[];
extern PADREQUEST B_004507C0;
s32 scePadSetActAlign(s32 port, s32 slot, u8 *data) {
    PADREQUEST *request = &B_004507C0;
    s32 index;
    request->command = 8;
    request->port = port;
    request->slot = slot;
    for (index = 0; index < 6; index++) {
        request->arguments.bytes[index] = data[index];
    }
    if (sceSifCallRpc(B_00450580, 1, 0, request, 0x80, request, 0x80, 0, 0) < 0) {
        return 0;
    }
    if (request->result == 1) {
        func_00243458(port, slot, 2);
    }
    return request->result;
}
}
