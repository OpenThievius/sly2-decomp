// SPDX-License-Identifier: GPL-3.0-or-later
#include "sohit.h"
#include "oxa.h"

/* a SOHIT subclass by its fields from 0x1C0 (the Splice binding RefCall180478 is of the SOHIT family, whose own fields start there); class unnamed */
struct FilterObject : SOHIT {
    /* 0x1C0 */ float result;  /* reader: func_00180478 */
    /* 0x1C4 */ float fraction;
    /* 0x1C8 */ s32 mode;
};

extern "C" {
void RecalcSwOxfFilterForObject(char *, FilterObject *);
extern char B_003DD490[];
extern float g_2a5654;
extern float g_2dded0;
}

extern "C" void func_00180478(FilterObject *object, s32 mode)
{
    if (mode != object->mode) {
        object->mode = mode;
        if (object->poxa->owner == object) {
            RecalcSwOxfFilterForObject(B_003DD490, object);
        }
    }
    float fraction = object->fraction;
    float result;
    if (fraction != 0.0f) {
        result = g_2dded0 + fraction;
    } else {
        result = g_2a5654;
    }
    object->result = result;
}
