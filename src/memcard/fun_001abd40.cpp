// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"

#include "memcard.h"





struct SAVEVARS;
struct Bytes8 { s64 v; } __attribute__((packed));

extern "C" {
void CreateMemcardThread__FP7MEMCARDii(MEMCARD *, s64);
void SnapshotSaveData(SAVEVARS *, SAVEDATA *);
void StoreAudioModeInSave();
extern SAVEVARS B_003E0EA8;
extern Bytes8 RO_002A6C90;
void func_001ABD40(SAVE *save) {
    StoreAudioModeInSave();
    SnapshotSaveData(&B_003E0EA8, &save->pslotCur->data);
    CreateMemcardThread__FP7MEMCARDii(&save->mc, RO_002A6C90.v);
}
}
