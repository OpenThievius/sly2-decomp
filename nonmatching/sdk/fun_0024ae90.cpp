#include "types.h"
extern "C" {
typedef struct {
    char pad0[0x18];
    s64 f18;
    s64 f20;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
    s32 f40;
    s32 f44;
    s32 f48;
    s32 f4C;
    s32 f50;
    s32 f54;
    s32 f58;
    s32 f5C;
    s32 f60;
} FRAME;
typedef struct {
    char pad0[0xB4];
    s32 fB4;
    s32 fB8;
    char padBC[0x40];
    s32 fFC;
    char pad100[0x4C];
    s32 f14C;
    char pad150[0x8];
    s32 f158;
    s32 f15C;
    s32 f160;
    char pad164[0x20];
    s32 f184;
    s32 f188;
    char pad18C[0x8];
    s32 f194;
    s32 f198;
    s32 f19C;
    s32 f1A0;
    s32 f1A4;
    s32 f1A8;
    s32 f1AC;
    s32 f1B0;
    s32 f1B4;
    s32 f1B8;
    char pad1BC[0xC];
    FRAME *f1C8;
    FRAME *f1CC;
    FRAME *f1D0;
    FRAME *f1D4;
    FRAME *f1D8;
    FRAME *f1DC;
    FRAME *f1E0;
    FRAME *f1E4;
    FRAME *f1E8;
    FRAME *f1EC;
    FRAME *f1F0;
    FRAME *f1F4;
    char pad1F8[0x640];
    s64 f838;
    s64 f840;
} SLOTS;

int func_0024AE90(SLOTS *obj, int arg1) {
    FRAME *frame = 0;
    FRAME *ref;
    int one;
    int result = 0;
    int state = obj->f184;
    int mode = obj->f160;
    int limit = (state == 3) ? 2 : 4;
    if (mode == 3) {
        obj->f1D0 = obj->f1D4;
        obj->f1E0 = obj->f1E4;
        obj->f1F0 = obj->f1F4;
        if (obj->fB4 + obj->fB8 >= limit) {
            obj->fFC = 0;
            obj->f1B8 = 0;
            obj->f1B4 = 0;
        }
        if ((obj->fFC != 0 || obj->f1B8 != 0) && obj->f1B4 == 0) {
            obj->f1C8->f28 = 0;
            obj->f1D8->f28 = 0;
            obj->f1E8->f28 = 0;
            state = obj->f184;
        }
        obj->fFC = 0;
        obj->f1B8 = 0;
        if (state == 3) {
            one = 1;
            if (obj->f1C8->f28 == 1 || obj->f1B4 != 0) {
                ref = obj->f1CC;
                goto tail;
            }
        } else {
            one = obj->f1D8->f28;
            if ((one == 1 && obj->f1E8->f28 == one) || obj->f1B4 != 0) {
                one = obj->f1DC->f28;
                if (one == 1) {
                    ref = obj->f1EC;
                tail:
                    result = one;
                    if ((ref->f28 ^ 1) != 0) {
                        result = 0;
                    }
                }
            }
        }
    } else {
        if (arg1 == 0) {
            FRAME *first = obj->f1C8;
            FRAME *second = obj->f1CC;
            obj->f1CC = first;
            first = obj->f1D8;
            FRAME *third = obj->f1DC;
            obj->f1DC = first;
            first = obj->f1E8;
            FRAME *fourth = obj->f1EC;
            obj->f1C8 = second;
            obj->f1D8 = third;
            obj->f1E8 = fourth;
            obj->f1EC = first;
        }
        obj->f1D0 = obj->f1CC;
        obj->f1E0 = obj->f1DC;
        obj->f1F0 = obj->f1EC;
        if (state == 3) {
            if (mode == 2) {
                if (obj->f1C8->f28 == 1) {
                    result = 1;
                }
            } else {
                result = 1;
            }
        } else if (mode != 2) {
            result = 1;
        } else {
            FRAME *chosen = (state != 1) ? obj->f1DC : obj->f1EC;
            if (arg1 != 0 && chosen->f28 == 1) {
                result = 1;
            } else {
                int first = obj->f1D8->f28;
                if (first == 1 && obj->f1E8->f28 == first) {
                    result = 1;
                }
            }
        }
    }
    switch (state) {
    case 1:
        frame = obj->f1E0;
        break;
    case 3:
        frame = obj->f1D0;
        break;
    case 2:
        frame = obj->f1F0;
        break;
    }
    frame->f28 = 0;
    frame->f18 = obj->f838;
    frame->f2C = obj->f160;
    frame->f20 = obj->f840;
    frame->f30 = obj->f184;
    frame->f34 = obj->f14C;
    frame->f38 = obj->f198;
    frame->f3C = obj->f188;
    frame->f40 = obj->f194;
    frame->f44 = obj->f19C;
    frame->f48 = obj->f1A0;
    frame->f4C = obj->f1A4;
    frame->f50 = obj->f1A8;
    frame->f54 = obj->f1AC;
    frame->f58 = obj->f1B0;
    frame->f5C = obj->f158;
    frame->f60 = obj->f15C;
    return result;
}
}
