/* SPDX-License-Identifier: GPL-3.0-or-later */
/* A singly linked list header as AppendSlEntry (0x11A070) reads it: first and last entry, and the offset of the link word inside
   an entry. Users: Vector_Init, func_00256528 (both append a cursor to one). C and C++. */
#ifndef SLY2_SL_H
#define SLY2_SL_H
#include "types.h"
typedef struct SL {
    void *pvFirst;
    void *pvLast;
    s32 ibSle;
} SL;
#endif
