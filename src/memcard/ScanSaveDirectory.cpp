// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "types.h"

#include "memcard.h"





extern "C" {
int sceMcGetDir(int, int, const char *, int, int, int);
int McSync(void *, int, int, int *);
int GetCardFreeBytes(SAVE *, int *);
int ReadSaveSlot(SAVE *, SLOT *);
}
extern char RO_002A6BB0[];
extern "C" int ScanSaveDirectory(SAVE *save)
{
    int ac[2];
    MEMCARD *card = &save->mc;
    int start = sceMcGetDir(save->port, save->slot, RO_002A6BB0, 0, -1, 0);
    int error = McSync(card, start, 0xD, &ac[0]);
    if (ac[0] < 1) {
        GetCardFreeBytes(save, &ac[1]);
        if (ac[1] < 0x19000)
            save->cardState = 4;
        return 0xE;
    }
    int islot = 0;
    if (error == 0) {
        SLOT *slot = save->aslot;
        do {
            ReadSaveSlot(save, slot);
            slot++;
            islot++;
        } while (error == 0 && islot < 3);
        if (error == 0) {
            if (save->cardState < 5)
                save->cardState = 5;
        }
    }
    return error;
}
