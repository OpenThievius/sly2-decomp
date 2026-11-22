/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

/* One entry of a memory card directory listing as the card library writes it (the callee of McSync's directory read): created and
   modified stamps as seconds..year, a size, attribute bits, and the file name at 0x20. */
typedef struct MCDIRENTRY {
    /* 0x00 */ u8 unknown_0x0;
    /* 0x01 */ u8 createSecond;
    /* 0x02 */ u8 createMinute;
    /* 0x03 */ u8 createHour;
    /* 0x04 */ u8 createDay;
    /* 0x05 */ u8 createMonth;
    /* 0x06 */ u16 createYear;
    /* 0x08 */ u8 unknown_0x8;
    /* 0x09 */ u8 modifySecond;
    /* 0x0A */ u8 modifyMinute;
    /* 0x0B */ u8 modifyHour;
    /* 0x0C */ u8 modifyDay;
    /* 0x0D */ u8 modifyMonth;
    /* 0x0E */ u16 modifyYear;
    /* 0x10 */ s32 size;
    /* 0x14 */ u16 attributes;
    /* 0x16 */ u8 unknown_0x16[0xA];
    /* 0x20 */ char name[0x20];
} MCDIRENTRY;

#include "memcard.h"

void *memset(void *, int, unsigned int);
char *strcpy(char *, const char *);

void ConvertMcDirEntry(MCDIRENTRY *entry, MCFILEINFO *info) {
    memset(info, 0, 0x5C);
    strcpy(info->name, entry->name);
    info->size = entry->size;
    if (entry->attributes & 1) {
        info->flags = info->flags | 1;
    }
    if (entry->attributes & 2) {
        info->flags = info->flags | 2;
    }
    if (entry->attributes & 4) {
        info->flags = info->flags | 4;
    }
    if (entry->attributes & 8) {
        info->flags = info->flags | 8;
    }
    if (entry->attributes & 0x20) {
        info->flags = info->flags | 0x10;
    }
    if (entry->attributes & 0x80) {
        info->flags = info->flags | 0x20;
    }
    if (entry->attributes & 0x800) {
        info->flags = info->flags | 0x40;
    }
    if (entry->attributes & 0x1000) {
        info->flags = info->flags | 0x80;
    }
    info->createMonth = entry->createMonth;
    info->createDay = entry->createDay;
    info->createYear = entry->createYear;
    info->createHour = entry->createHour;
    info->createMinute = entry->createMinute;
    info->createSecond = entry->createSecond;
    info->modifyMonth = entry->modifyMonth;
    info->modifyDay = entry->modifyDay;
    info->modifyYear = entry->modifyYear;
    info->modifyHour = entry->modifyHour;
    info->modifyMinute = entry->modifyMinute;
    info->modifySecond = entry->modifySecond;
}
