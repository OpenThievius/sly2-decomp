#include "types.h"
#include "sl.h"

typedef struct BLOTMOVIE {
    u8 unknown_0x0[0x44];
    s32 field_0x44;
    s32 field_0x48;
} BLOTMOVIE;

typedef struct BLOT {
    /* the members below mirror BASIC, LO (lo.h) and BLOT (blot.h) up to 0xFC: a C source cannot include those C++ headers */
    s32 field_0x0;                   /* BASIC::pframe */
    s32 field_0x4;                   /* BASIC::psidebag */
    s32 field_0x8;                   /* BASIC::psubFirst */
    s32 *field_0xC;                  /* the vtable pointer */
    void *psoParent;                 /* LO 0x10 */
    s32 proot;                       /* LO 0x14 */
    s32 oid;                         /* LO 0x18 */
    u8 unknown_0x1C[0x4];
    void *ploNextCid;                /* LO 0x20 */
    void *ploNext;                   /* LO 0x24 */
    u64 grfo;                        /* LO 0x28 */
    f32 tUpdate;                     /* LO 0x30 */
    void *pdcb;                      /* LO 0x34 */
    f32 field_0x38;                  /* LO 0x38 */
    void *pscope;                    /* LO 0x3C */
    u32 grfSw;                       /* LO 0x40 */
    u8 unknown_0x44[0xC];
    s32 field_0x50;
    s32 field_0x54;
    s32 blots;                       /* blot.h */
    f32 time;
    s32 tagState;
    s32 field_0x64;
    f32 tLast;                       /* 0x68, blot.h */
    u8 unknown_0x6C[0x1];
    u8 field_0x6D;
    u8 unknown_0x6E[0x2];
    s32 labelVisible;
    s32 labelAppear;
    s32 labelDisappear;
    s32 cur;
    s16 csprite;
    u8 unknown_0x82[0x2];
    s32 asprite;
    f32 labelTime;
    s32 field_0x8C;
    f32 dwell;
    s32 height;
    s32 width;
    f32 field_0x9C;
    f32 field_0xA0;
    s32 order;
    s32 field_0xA8;
    s32 modal;
    s32 fSlowsClock;
    u8 unknown_0xB4[0x8];
    s32 field_0xBC;
    BLOTMOVIE *field_0xC0;           /* blot.h: pstream */
    void *palloc;
    void *pblotSelf;
    s32 alabel[10];
    u8 unknown_0xF4[0x4];
    s32 field_0xF8;
    SL sl;                           /* 0xFC */
    u8 unknown_0x108[0x8];
    s32 field_0x110;
    s32 field_0x114;
    s32 field_0x118;
    s32 field_0x11C;
    s32 field_0x120;
} BLOT;

extern f32 g_2ddf0c;

void SetTimerTimers__FP5TIMER6TIMERS(BLOT *arg0, s32 arg1) {
    if (arg0->field_0x64 != arg1) {
        arg0->field_0x64 = arg1;
        arg0->tLast = g_2ddf0c;
    }
}
