#include "types.h"

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
    u8 unknown_0x60[0x4];
    s32 field_0x64;
    f32 field_0x68;
    u8 unknown_0x6C[0xC];
    s32 field_0x78;
    u8 unknown_0x7C[0x4];
    s16 field_0x80;
    u8 unknown_0x82[0x2];
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

s32 AppendDlEntry(s32 *, BLOT *);
s32 FFindDlEntry(s32 *, BLOT *);
s32 RemoveDlEntry(s32 *, BLOT *);
extern s32 B_003E1060;

void SetBlotModal(BLOT *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = arg0->field_0xA8;
    if (temp_v0 != arg1) {
        if ((temp_v0 == 0) && (FFindDlEntry(&B_003E1060, arg0) != 0)) {
            RemoveDlEntry(&B_003E1060, arg0);
        }
        arg0->field_0xA8 = arg1;
        if ((arg1 == 0) && (FFindDlEntry(&B_003E1060, arg0) == 0)) {
            AppendDlEntry(&B_003E1060, arg0);
        }
    }
}
