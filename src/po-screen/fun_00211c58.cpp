#include "types.h"
extern "C" {
typedef struct BLOTMOVIE {
    u8 unknown_0x0[0x44];
    s32 field_0x44;
    s32 field_0x48;
} BLOTMOVIE;

typedef struct BLOT {
    u8 unknown_0x0[0xC];
    s32 *field_0xC;
    u8 unknown_0x10[0x40];
    s32 field_0x50;
    s32 field_0x54;
    s32 field_0x58;
    f32 field_0x5C;
    u8 unknown_0x60[4];
    s32 field_0x64;
    f32 field_0x68;
    u8 unknown_0x6C[0xC];
    s32 field_0x78;
    u8 unknown_0x7C[4];
    s16 field_0x80;
    u8 unknown_0x82[2];
    s32 field_0x84;
    u8 unknown_0x88[0x20];
    s32 field_0xA8;
    u8 unknown_0xAC[0x14];
    BLOTMOVIE *field_0xC0;
    u8 unknown_0xC4[0x34];
    s32 field_0xF8;
    char field_0xFC[0x14];
    s32 field_0x110;
    s32 field_0x114;
    s32 field_0x118;
    s32 field_0x11C;
    s32 field_0x120;
} BLOT;

s32 Blot_Construct(BLOT *);
extern s32 D_002C9670;

BLOT *func_00211C58(BLOT *arg0) {
    Blot_Construct(arg0);
    arg0->field_0x110 = -1;
    arg0->field_0xC = &D_002C9670;
    arg0->field_0x114 = -1;
    arg0->field_0x118 = -1;
    arg0->field_0x11C = -1;
    arg0->field_0x120 = -1;
    return arg0;
}

}
