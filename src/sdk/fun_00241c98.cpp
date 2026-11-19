extern "C" {
int sceSifBindRpc(int *client, unsigned int rpcNumber, unsigned int mode);
void sceSifInitRpc(int);
int PollSema(int);
void SignalSema(int);
int sceCdSync(int);
void func_00236960(const char *, ...);
void func_00241A30(void);
extern int D_002C6750;
extern int D_002C675C;
extern volatile int D_002C6768; // volatile-ok: semaphore id shared with the CD library's other threads
extern int D_002C677C;
extern int D_002C7910[];

int func_00241C98(int command)
{
    int spinCount;
    func_00241A30();
    if (D_002C6768 != PollSema(D_002C6768)) {
        if (D_002C6750 > 0) {
            func_00236960("Ncmd fail sema cur_cmd:%d keep_cmd:%d\n", command, D_002C675C);
        }
        return 0;
    }
    D_002C675C = command;
    if (sceCdSync(1) != 0) {
        SignalSema(D_002C6768);
        return 0;
    }
    sceSifInitRpc(0);
    if (D_002C677C < 0) {
        for (;;) {
            if (sceSifBindRpc(D_002C7910, 0x80000595, 0) < 0) {
                if (D_002C6750 > 0) {
                    func_00236960("Libcdvd bind err N CMD\n");
                }
                spinCount = 0x100000;
                do {
                    spinCount--;
                } while (spinCount != -1);
            } else {
                if (D_002C7910[9] != 0) {
                    D_002C677C = 0;
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
