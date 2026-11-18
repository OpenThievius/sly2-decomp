#include "types.h"

struct RpcClientData {
    int words[9];
    int serverReady;
};

extern s32 D_002C676C;
extern s32 D_002C6750;
extern s32 D_002C6758;
extern s32 D_002C6794;
extern struct RpcClientData D_002C82C0;

void func_00241A30(void);
s32 PollSema(s32 semaphoreId);
void SignalSema(s32 semaphoreId);
s32 func_00241F28(s32 value);
void sceSifInitRpc(s32 flags);
s32 sceSifBindRpc(struct RpcClientData *client, u32 number, u32 mode);
void func_00236960(const char *format, ...);

s32 func_00241F98(s32 cmd)
{
    s32 spinCount;

    func_00241A30();
    if (D_002C676C != PollSema(D_002C676C)) {
        if (D_002C6750 > 0)
            func_00236960("Scmd fail sema cur_cmd:%d keep_cmd:%d\n", cmd, D_002C6758);
        return 0;
    }
    D_002C6758 = cmd;
    if (func_00241F28(1) != 0) {
        SignalSema(D_002C676C);
        return 0;
    }
    sceSifInitRpc(0);
    if (D_002C6794 >= 0)
        return 1;
    for (;;) {
        if (sceSifBindRpc(&D_002C82C0, 0x80000593, 0) < 0) {
            if (D_002C6750 > 0)
                func_00236960("Libcdvd bind err S cmd\n");
        } else if (D_002C82C0.serverReady != 0) {
            D_002C6794 = 0;
            return 1;
        }
        spinCount = 0x100000;
        do {
            spinCount -= 1;
        } while (spinCount != -1);
    }
}
