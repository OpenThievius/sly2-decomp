/* SPDX-License-Identifier: GPL-3.0-or-later */
typedef unsigned int u32;
typedef struct SifEntry {
    void (*function)();
    void *argument;
    int unused;
} SifEntry;
typedef struct SifState {
    u32 sendUncached;
    u32 receiveUncached;
    int registerValue;
    SifEntry *entries;
    int count;
    int field14;
    int field18;
    u32 *list;
} SifState;
typedef struct SifPacket {
    char pad0[0xC];
    int field0C;
    void *buffer;
} SifPacket;
int AddDmacHandler(int, void *, int);
void FlushCache(int);
void func_00235248(int);
void func_00239450();
void func_002394A0(void);
int func_0023AFA8(unsigned int, void *, int, int, int, int);
int sceSifGetReg(unsigned int);
void sceSifSetDChain();
void sceSifSetReg(unsigned int, int);
extern char B_0044ED00[];
extern char B_0044ED80[];
extern SifPacket B_0044EDC0;
extern int B_0044EDD4;
extern SifState B_0044EDD8;
extern SifEntry B_0044EE00[32];
extern u32 B_0044EF80[32];
extern int D_002C5A60;
void func_0023AA98();
void func_0023AAB8();
extern char func_0023B028[];

void func_0023AAF0(void)
{
    SifEntry *entry;
    int index;
    int registerValue;
    int value;
    func_00239450();
    if (D_002C5A60 != 0) {
        func_002394A0();
        return;
    }
    D_002C5A60 = 1;
    B_0044EDD8.sendUncached = (u32)B_0044ED00 | 0x20000000;
    B_0044EDD8.receiveUncached = (u32)B_0044ED80 | 0x20000000;
    B_0044EDD8.registerValue = 0;
    B_0044EDD8.entries = B_0044EE00;
    B_0044EDD8.count = 0x20;
    B_0044EDD8.field14 = 0;
    B_0044EDD8.field18 = 0;
    B_0044EDD8.list = B_0044EF80;
    entry = B_0044EE00;
    do {
        entry->function = 0;
        entry->argument = 0;
        entry++;
    } while ((int)entry < (int)(B_0044EE00 + 32));
    for (index = 0x1F; index >= 0; index--) {
        B_0044EF80[index] = 0;
    }
    index = 0x20;
    B_0044EE00[0].function = func_0023AAB8;
    B_0044EE00[1].function = func_0023AA98;
    B_0044EE00[0].argument = &B_0044EDD8;
    B_0044EE00[1].argument = &B_0044EDD8;
    func_002394A0();
    FlushCache(0);
    if (*(volatile u32 *)0x1000E010 & 0x20)
        *(volatile u32 *)0x1000E010 = index;
    if (!(*(volatile u32 *)0x1000C000 & 0x100))
        sceSifSetDChain();
    B_0044EDD4 = AddDmacHandler(5, func_0023B028, 0);
    func_00235248(5);
    registerValue = sceSifGetReg(0x80000000);
    B_0044EDD8.registerValue = registerValue;
    if (registerValue != 0) {
        B_0044EDC0.buffer = B_0044ED00;
        func_0023AFA8(0x80000000, &B_0044EDC0, 0x14, 0, 0, 0);
        return;
    }
    while (!(sceSifGetReg(4) & 0x20000)) {
    }
    value = sceSifGetReg(2);
    B_0044EDD8.registerValue = value;
    sceSifSetReg(0x80000000, value);
    sceSifSetReg(0x80000001, (int)&B_0044EDD8);
    B_0044EDC0.field0C = 0;
    B_0044EDC0.buffer = B_0044ED00;
    func_0023AFA8(0x80000002, &B_0044EDC0, 0x14, 0, 0, 0);
}
