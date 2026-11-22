/* SPDX-License-Identifier: GPL-3.0-or-later */
/* What a class factory writes (the func_0011xxxx `new` functions of new_100008): the factory allocates the instance with
   __builtin_new, then runs the inlined constructor chain, which stores each class's vtable pointer at 0xC in turn and clears
   BASIC's first two words. C++ cannot store a vtable pointer by hand, so the factories are written in C on this view of the
   instance's first 0x10 bytes; lo.h's BASIC is the same object as the game's C++ code sees it (0x4 is its psidebag).
   Fields past 0x10 that a constructor clears are reached through the views below (NEWSO and the views built on it, NEWSUB30,
   NEWSUB3, NEWCLEARED30): each holds only the words the factories store, unknown gaps as unknown_0xOFF; a view is not the
   class's size. C and C++. */
#ifndef SLY2_FACTORY_H
#define SLY2_FACTORY_H
#include "types.h"
#include "globset.h"

/* operator new by its symbol: the factories allocate with it before running the constructor chain */
#ifdef __cplusplus
extern "C" void *__builtin_new(unsigned int cb);
#else
void *__builtin_new(unsigned int cb);
#endif

typedef struct NEWBASIC {
    /* 0x0 */ s32 field_0x0;     /* BASIC's first word: every factory clears it */
    /* 0x4 */ void *psidebag;    /* BASIC::psidebag: every factory clears it */
    /* 0x8 */ s32 field_0x8;
    /* 0xC */ const void *pvtbl; /* the vtable of the class whose constructor runs: each constructor of the chain stores its own */
} NEWBASIC;

/* An instance of SO (class 48, 0x150 bytes, vtable 0x2D9978 = D_002D9978) or of a class derived from it: SO's constructor stores
   its vtable, clears BASIC's two words and constructs the globset at 0x80 (GLOBSET::GLOBSET, out of line). field_0x174 lies
   past SO, in PO's range (po.h, 0x180 bytes): a constructor between SO and the class clears it (14 factories from func_00111628
   to func_00111DE8, ConstructGuard's f174, ConstructSly and ConstructMurray); the factories of SO itself and of classes that do
   not derive through it leave it alone. */
typedef struct NEWSO {
    /* 0x0 */ NEWBASIC basic;
    u8 unknown_0x10[0x70];
    /* 0x80 */ GLOBSET globset;
    u8 unknown_0xD0[0xA4];
    /* 0x174 */ s32 field_0x174;
} NEWSO;

/* Class 72 (0x2B0 bytes, vtable 0x2D15D0): its constructor also clears the word at 0x2A4 (func_00111BC8, the one reader) */
typedef struct NEWSO2A4 {
    /* 0x0 */ NEWSO so;
    u8 unknown_0x178[0x12C];
    /* 0x2A4 */ s32 field_0x2A4;
} NEWSO2A4;

/* Class 77 (0x5D0 bytes, vtable 0x2D7CA8): its constructor also clears the word at 0x598 (func_00111D88, the one reader) */
typedef struct NEWSO598 {
    /* 0x0 */ NEWSO so;
    u8 unknown_0x178[0x420];
    /* 0x598 */ s32 field_0x598;
} NEWSO598;

/* Sub-objects of 0x20 bytes that func_002562A8 constructs (it clears their first two words): one at 0x30 (func_00113840),
   three at 0x40, 0x60 and 0x80 (func_00113708) */
typedef struct NEWSUB30 {
    /* 0x0 */ NEWBASIC basic;
    u8 unknown_0x10[0x20];
    /* 0x30 */ u8 sub_0x30[0x20];
} NEWSUB30;

typedef struct NEWSUB3 {
    /* 0x0 */ NEWBASIC basic;
    u8 unknown_0x10[0x30];
    /* 0x40 */ u8 sub_0x40[0x20];
    /* 0x60 */ u8 sub_0x60[0x20];
    /* 0x80 */ u8 sub_0x80[0x20];
} NEWSUB3;

/* A block of 0x70 bytes at 0x30 that the constructor clears with memset (func_00113060) */
typedef struct NEWCLEARED30 {
    /* 0x0 */ NEWBASIC basic;
    u8 unknown_0x10[0x20];
    /* 0x30 */ u8 cleared_0x30[0x70];
} NEWCLEARED30;

#if defined(__mips__)
typedef char check_NEWBASIC_size[(sizeof(NEWBASIC) == 0x10) ? 1 : -1];
typedef char check_NEWSO_size[(sizeof(NEWSO) == 0x178) ? 1 : -1];
typedef char check_NEWSO2A4_size[(sizeof(NEWSO2A4) == 0x2A8) ? 1 : -1];
typedef char check_NEWSO598_size[(sizeof(NEWSO598) == 0x59C) ? 1 : -1];
typedef char check_NEWSUB30_size[(sizeof(NEWSUB30) == 0x50) ? 1 : -1];
typedef char check_NEWSUB3_size[(sizeof(NEWSUB3) == 0xA0) ? 1 : -1];
typedef char check_NEWCLEARED30_size[(sizeof(NEWCLEARED30) == 0xA0) ? 1 : -1];
#endif
#endif
