// SPDX-License-Identifier: GPL-3.0-or-later
extern "C" {
struct SndCall {
    void (*function)(int, long);
    long argument;
};
struct SndRpcClient {
    char pad0[0x24];
    int serverReady;
    char pad28[0x18];
};
struct SndReturnBuffer {
    volatile int field0; // volatile-ok: IOP-side 989snd writes this return word over SIF DMA
    char pad4[0xC];
    volatile int field10; // volatile-ok: IOP-side 989snd writes this return word over SIF DMA
    char pad14[0x2C];
};
struct SndStartCommand {
    SndReturnBuffer *returns;
    unsigned int flags;
};
int func_002325E0(int command, int size, void *payload);
int printf(const char *, ...);
int sceSifBindRpc(SndRpcClient *client, int serverId, int mode);
void sceSifInitRpc(int mode);
extern SndRpcClient B_00443800;
extern int B_00443B80[];
extern int B_00444B80[];
extern SndCall B_00445B80[];
extern SndCall B_00446B80[];
extern int B_00447B80[];
extern int B_00447FC0[];
extern SndReturnBuffer B_00448400;
extern SndRpcClient B_00448440;
extern unsigned int B_00448480;
extern int *D_002C4660[];
extern int D_002C4668[];
extern SndCall *D_002C4670[];
extern int *D_002C4678[];
extern int D_002C4688;
extern SndCall D_002C4690;
extern int D_002C46B8;

void snd_StartSoundSystem(unsigned int flags) {
    SndStartCommand command;
    int delay;
    D_002C4660[0] = B_00443B80;
    D_002C4660[1] = B_00444B80;
    D_002C4678[0] = B_00447B80;
    D_002C4678[1] = B_00447FC0;
    D_002C4670[0] = B_00445B80;
    D_002C4670[1] = B_00446B80;
    if (flags & 2) {
        D_002C46B8 = 1;
    } else {
        D_002C46B8 = 0;
    }
    sceSifInitRpc(0);
    for (;;) {
        if (sceSifBindRpc(&B_00443800, 0x123456, 0) < 0) {
            printf("error: sceSifBindRpc in %s, at line %d\n", "c:\\vss\\p3/989snd.cpp", 181);
            for (;;) {
            }
        }
        for (delay = 0x270F; delay != -1; delay--) {
        }
        if (B_00443800.serverReady != 0) {
            break;
        }
    }
    D_002C4688 = 0;
    D_002C4690.function = 0;
    D_002C4690.argument = 0;
    B_00448480 = 0;
    for (;;) {
        if (sceSifBindRpc(&B_00448440, 0x123457, 0) < 0) {
            printf("error: sceSifBindRpc in %s, at line %d\n", "c:\\vss\\p3/989snd.cpp", 202);
            for (;;) {
            }
        }
        for (delay = 0x270F; delay != -1; delay--) {
        }
        if (B_00448440.serverReady != 0) {
            break;
        }
    }
    B_00448400.field0 = 0;
    B_00448400.field10 = 0;
    D_002C4668[0] = 0xFFC;
    D_002C4668[1] = 0xFFC;
    B_00443B80[0] = 0;
    B_00444B80[0] = 0;
    command.returns = &B_00448400;
    command.flags = flags;
    func_002325E0(0, 8, &command);
}
}
