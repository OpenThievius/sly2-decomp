/* SPDX-License-Identifier: GPL-3.0-or-later */
struct CdReadCommand {
    int lsn;
    int sectors;
    void *buffer;
    unsigned char mode[3];
    void *result;
    void *status;
};

extern int D_002C6778;
extern int D_002C6750;
extern int D_002C67A0;
extern int D_002C6774;
extern int D_002C6768;
extern struct CdReadCommand D_002C6840;
extern char D_002C7840[];
extern int D_002C7900;
extern char D_002C7910[];

int func_00241DF0(int, int, void *);
int func_00241C98(int);
void func_0023B170(void *, int);
void func_00236960(const char *, ...);
int sceSifCallRpc(void *, int, int, void *, int, void *, void *, void *, void *);
void SignalSema(int);
void func_00241978(void);

int sceCdRead(int lsn, int sectors, void *buffer, unsigned char *mode)
{
    struct CdReadCommand *command = &D_002C6840;
    int size;

    if ((D_002C6778 & 1) || func_00241DF0(lsn, sectors, buffer) != 6) {
        if (func_00241C98(4) == 0) {
            return 0;
        }
        command->lsn = lsn;
        command->sectors = sectors;
        command->buffer = buffer;
        command->mode[0] = mode[0];
        command->mode[1] = mode[1];
        command->mode[2] = mode[2];
        command->result = D_002C7840;
        command->status = &D_002C7900;
        switch (mode[2]) {
        case 1:
            size = sectors * 0x918;
            break;
        case 2:
            size = sectors * 0x924;
            break;
        default:
            size = sectors << 11;
            break;
        }
        D_002C7900 = 0;
        if (!(D_002C6778 & 2)) {
            func_0023B170(buffer, size);
        }
        func_0023B170(D_002C7840, 0x90);
        func_0023B170(command, 0x18);
        func_0023B170(&D_002C7900, 4);
        if (D_002C6750 > 0) {
            func_00236960("call cdread cmd\n");
        }
        D_002C67A0 = 1;
        D_002C6774 = 1;
        if (sceSifCallRpc(D_002C7910, 1, 1, command, 0x18, 0, 0, func_00241978, D_002C7840) < 0) {
            D_002C67A0 = 0;
            SignalSema(D_002C6768);
            D_002C6774 = 0;
            return 0;
        }
        if (D_002C6750 > 0) {
            func_00236960("cdread end\n");
        }
        return 1;
    }
    return 0;
}
