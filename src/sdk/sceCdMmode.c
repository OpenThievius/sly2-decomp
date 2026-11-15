/* SPDX-License-Identifier: GPL-3.0-or-later */
extern int D_002C676C;
extern int D_002C7D80;
extern char B_002C82C0[];
extern int B_002C7940[];
extern int D_002C82E8;
extern int D_002C82EC;
extern int D_002C82F0;
extern int func_00241F98(int);
extern void func_0023B170(void *, int);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, int, int);
extern int SignalSema(int);
int sceCdMmode(int mode)
{
    int *modeSlot = &D_002C7D80;
    int result;
    if (func_00241F98(0x22) == 0)
        return 0;
    *modeSlot = mode;
    func_0023B170(modeSlot, 4);
    if (sceSifCallRpc(B_002C82C0, D_002C82E8, 0, modeSlot, D_002C82EC, B_002C7940, D_002C82F0, 0, 0) < 0) {
        SignalSema(D_002C676C);
        return 0;
    }
    result = *(int *)((unsigned int)B_002C7940 | 0x20000000);
    SignalSema(D_002C676C);
    return result;
}
