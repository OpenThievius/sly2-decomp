extern "C" {
int sceSifBindRpc(int *client, unsigned int rpcNumber, unsigned int mode);
void sceSifInitRpc(int);
int PollSema(int);
void SignalSema(int);
int func_00241F28(int);
void func_00236960(const char *, ...);
void func_00241A30(void);
extern int D_002C6750;
extern int D_002C6758;
extern volatile int D_002C676C; // volatile-ok: semaphore id shared with the CD library's other threads
extern int D_002C6794;
extern int D_002C82C0[];

int func_00241F98(int command)
{
    int spinCount;
    func_00241A30();
    if (D_002C676C != PollSema(D_002C676C)) {
        if (D_002C6750 > 0) {
            func_00236960("Scmd fail sema cur_cmd:%d keep_cmd:%d\n", command, D_002C6758);
        }
        return 0;
    }
    D_002C6758 = command;
    if (func_00241F28(1) != 0) {
        SignalSema(D_002C676C);
        return 0;
    }
    sceSifInitRpc(0);
    if (D_002C6794 < 0) {
        for (;;) {
            if (sceSifBindRpc(D_002C82C0, 0x80000593, 0) < 0) {
                if (D_002C6750 > 0) {
                    func_00236960("Libcdvd bind err S cmd\n");
                }
                spinCount = 0x100000;
                do {
                    spinCount--;
                } while (spinCount != -1);
            } else {
                if (D_002C82C0[9] != 0) {
                    D_002C6794 = 0;
                    break;
                }
                spinCount = 0x100000;
                do {
                    spinCount--;
                } while (spinCount != -1);
            }
        }
    }
    return 1;
}
}
