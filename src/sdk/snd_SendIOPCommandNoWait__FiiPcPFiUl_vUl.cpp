// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
typedef void (*SoundCallback)(int, u64);

struct SoundCallbackEntry {
    SoundCallback callback;
    int pad4;
    u64 value;
};

struct ExternalCommand {
    int field0;
    int field4;
    unsigned int length;
    char *data;
};

extern "C" {
void FlushCache(int);
void func_00231F38(void *, int);
void *memcpy(void *, const void *, unsigned int);
int printf(const char *, ...);
int sceSifCallRpc(void *, int, int, void *, int, void *, int, int, int);
int sceSifCheckStatRpc(void *);
int snd_FlushSoundCommands(void);
extern char B_00443800[];
extern int B_00443840[];
extern int D_002C4640;
extern int *D_002C4660[];
extern int D_002C4668[];
extern SoundCallbackEntry *D_002C4670[];
extern int D_002C4680;
extern int D_002C4684;
extern int D_002C46B8;
extern char RO_002AA1C8[];
extern char RO_002AA670[];
}

void snd_PostMessage(void);

void snd_SendIOPCommandNoWait(int command, int size, char *data, SoundCallback callback, u64 value)
{
    int paused = 0;
    int total;
    int attempts;
    char *destination;
    int index;

    if (D_002C4684 == 0 && D_002C4640 == 0 && size == 0 && callback == 0) {
        func_00231F38(B_00443840, 1);
        while (sceSifCheckStatRpc(B_00443800) != 0) {
            if (D_002C46B8 == 0) {
                printf(RO_002AA1C8);
            }
            snd_FlushSoundCommands();
            FlushCache(0);
        }
        sceSifCallRpc(B_00443800, command, 1, 0, 0, B_00443840, 0xC, 0, 0);
        return;
    }
    total = size + 4;
    attempts = 0;
    if (total % 4 != 0) {
        total += 4 - total % 4;
    }
    if (total > 0x200) {
        printf("989snd ERROR: command too large!\n");
        for (;;) {
        }
    }
    while (*D_002C4660[D_002C4680] == 0x100 || D_002C4668[D_002C4680] < total) {
        if (D_002C4684 != 0) {
            D_002C4684 = 0;
            paused = 1;
        }
        snd_FlushSoundCommands();
        if (attempts == 1 && D_002C46B8 == 0) {
            printf("snd_SendIOPCommandNoWait: BUFFER %d FULL(%d)! Sound stalled waiting for IOP comands to finish!\n", D_002C4680, *D_002C4660[D_002C4680]);
        }
        attempts++;
    }
    if (attempts != 0 && D_002C46B8 == 0) {
        printf(RO_002AA670, attempts);
    }
    if (paused) {
        D_002C4684 = 1;
    }
    destination = (char *)D_002C4660[D_002C4680] - (D_002C4668[D_002C4680] - 0x1000);
    *(short *)destination = command;
    destination += 2;
    *(short *)destination = size;
    destination += 2;
    if (command != 0x68) {
        for (index = 0; index < size; index++) {
            destination[index] = data[index];
        }
    } else {
        for (index = 0; index < 0xC; index++) {
            destination[index] = data[index];
        }
        memcpy(destination + 0xC, ((ExternalCommand *)data)->data, ((ExternalCommand *)data)->length);
    }
    D_002C4668[D_002C4680] -= total;
    D_002C4670[D_002C4680][*D_002C4660[D_002C4680]].callback = callback;
    D_002C4670[D_002C4680][*D_002C4660[D_002C4680]].value = value;
    snd_PostMessage();
}
