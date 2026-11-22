/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The save and memory card objects (src/memcard): SAVE, its three SLOTs (a SAVEDATA blob and the card's MCFILEINFO directory entry),
   and the MEMCARD manager at SAVE+0xFD5C. Fields and their readers are from the memcard functions (InitMemcard, CreateMemcardThread,
   FMemcardThreadValid, FormatMemcard, ScanSaveDirectory, SetSaveState, CompareSaves, ConvertMcDirEntry...). C and C++. */
#ifndef SLY2_MEMCARD_H
#define SLY2_MEMCARD_H
#include "types.h"

/* The same entry as the save code keeps it (slot + 0x5408, 0x5C bytes): name, size, our flag bits, then the stamps. */
typedef struct MCFILEINFO {
    /* 0x00 */ char name[0x44];
    /* 0x44 */ s32 size;
    /* 0x48 */ union {
        s32 flags; /* read and written as a word (lw/sw), while the date bytes below land on its upper half */
        struct {
            /* 0x48 */ u8 unknown_0x48[2];
            /* 0x4A */ u8 createMonth;
            /* 0x4B */ u8 createDay;
        };
    };
    /* 0x4C */ u16 createYear;
    /* 0x4E */ u8 createHour;
    /* 0x4F */ u8 createMinute;
    /* 0x50 */ u8 createSecond;
    /* 0x51 */ u8 unknown_0x51;
    /* 0x52 */ u8 modifyMonth;
    /* 0x53 */ u8 modifyDay;
    /* 0x54 */ u16 modifyYear;
    /* 0x56 */ u8 modifyHour;
    /* 0x57 */ u8 modifyMinute;
    /* 0x58 */ u8 modifySecond;
    /* 0x59 */ u8 unknown_0x59[3];
} MCFILEINFO;

/* a pointer to member function as g++ 2.95 stores it (8 bytes), copied as a whole */
typedef struct MCPMF { char b[8]; } MCPMF;
typedef struct MEMCARD {
    /* 0x00 */ s32 semaphoreId;
    /* 0x04 */ s32 threadId; /* -1 when there is no thread */
    /* 0x08 */ MCPMF pmf; /* the thread's start callback, 8 bytes copied from a constant */
    /* 0x10 */ s32 busy; /* 0x20 after InitMemcard, 0x21 once the thread is created */
} MEMCARD;

/* The game save blob; SAVEDATA of SnapshotSaveData (0x5408 bytes). */
typedef struct SAVEDATA {
    /* 0x0000 */ u8 unknown_0x0[0x5408];
} SAVEDATA;

/* A save slot: the blob and the memory card's directory entry for its file. */
typedef struct SLOT {
    /* 0x0000 */ SAVEDATA data;
    /* 0x5408 */ MCFILEINFO info;
} SLOT;

/* The save/memory card state machine object (0xFD6C+ bytes; its memory card manager sits at 0xFD5C). */
typedef struct SAVE {
    /* 0x0000 */ s32 port;
    /* 0x0004 */ s32 slot;
    /* 0x0008 */ s32 state; /* SetSaveState's state */
    /* 0x000C */ s32 cardState; /* CheckCardStatus and ScanSaveDirectory's result: 1 none, 2 unformatted, 3 formatted, 4, 5 */
    /* 0x0010 */ f32 tStamp; /* the time of the last state change */
    /* 0x0014 */ f32 tNext;
    /* 0x0018 */ s32 cardType;
    /* 0x001C */ s32 cFree;
    /* 0x0020 */ s32 formatted;
    /* 0x0024 */ SLOT aslot[3];
    /* 0xFD50 */ SLOT *pslotCur;
    /* 0xFD54 */ SLOT *pslotNewest;
    /* 0xFD58 */ SLOT *pslotInit;
    /* 0xFD5C */ MEMCARD mc;
} SAVE;

#endif
