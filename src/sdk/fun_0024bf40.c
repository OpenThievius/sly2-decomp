#include "types.h"
struct PIC {
    int f0; int f4; int f8; int fC; int f10; int pad14; s64 f18; s64 f20; int f28; int f2C; int f30; int f34; int f38;
    int f3C; int f40; int f44; int f48; int pad4C; int f50; int f54; int pad58; int f5C; int f60;
};
struct PKT { s64 r0; s64 r8; s64 dispfb1; s64 display1; s64 pmode1; s64 dispfb2; s64 display2; s64 pmode2; };
struct CTX {
    u8 unknown_0x0[8]; int f8; u8 unknown_0xC[0x8C - 0xC]; int f8C; s64 f90; int f98; int f9C; s64 fA0; u8 unknown_0xA8[0xC0 - 0xA8];
    int fC0; int fC4; int fC8; int fCC; int fD0; int fD4; int fD8; int fDC; int fE0; int fE4; u8 unknown_0xE8[0xF0 - 0xE8];
    int fF0; int fF4; int fF8; int fFC; s64 f100; int f108; u8 unknown_0x10C[0x128 - 0x10C]; int f128; u8 unknown_0x12C[0x184 - 0x12C];
    int f184; u8 unknown_0x188[0x834 - 0x188]; int f834; u8 unknown_0x838[0x868 - 0x838]; struct PKT *pkt;
};
extern char RO_002AC438[];
int func_00236918(char *, int, const char *, ...);
void func_0024FA38(struct CTX *, char *);
void func_0024C670(struct CTX *, struct PIC *);
void func_0024B9F0(struct CTX *, struct PIC *);

static inline void SetCircuit(struct CTX *p, s64 *pdispfb, s64 *pdisplay, s64 *ppmode, struct PIC *pic)
{
    if (p->f8C != 0 && pic->f18 < 0 && p->f98 >= 0) {
        int field = p->fA0;
        s64 odd = field & 1;
        s64 f90odd = p->f90 & 1;
        int bit = odd & (p->f9C & 1) & f90odd;
        int half = (p->f90 * field) >> 1;
        *pdispfb = p->f98 + (half + bit);
        if (odd & p->f90)
            p->f9C++;
    } else {
        *pdispfb = pic->f18;
    }
    if (p->f108 == 2 && p->f100 >= 0) {
        *pdispfb = p->f100;
        p->f108 = 0;
        p->f100 = -1;
    }
    *pdisplay = pic->f20;
    *ppmode = (s64)pic->f34 << 8 | (s64)pic->f38 << 7 | (s64)pic->f3C << 6 | (s64)pic->f40 << 5 | (s64)pic->f30 << 3 | (s64)pic->f2C;
}

/* whether the frame buffer holds the picture; reports it when it does not */
static inline int FCheckFrameSize(struct CTX *p, struct PIC *pic)
{
    char buf[0x100];
    int fOk;
    if (p->fF4 != 0)
        fOk = p->fF0 >= pic->f4 && p->fF4 >= pic->f8;
    else
        fOk = p->fF8 >= pic->fC * pic->f10;
    if (!fOk) {
        func_00236918(buf, 0x100, RO_002AC438, pic->f4, pic->f8);
        func_0024FA38(p, buf);
    }
    return fOk;
}

void func_0024BF40(struct CTX *p, struct PIC *pic1, struct PIC *pic2)
{
    int mask = 0;
    struct PIC *picA;
    struct PIC *picB;
    int fOk;

    if (p->f184 == 2) {
        picA = pic1;
        picB = pic2;
        mask = 0x40;
    } else {
        picA = pic2;
        picB = pic1;
    }
    SetCircuit(p, &p->pkt->dispfb1, &p->pkt->display1, &p->pkt->pmode1, picA);
    p->f98 = p->pkt->dispfb1;
    p->fA0 = 1;
    SetCircuit(p, &p->pkt->dispfb2, &p->pkt->display2, &p->pkt->pmode2, picB);
    p->f98 = p->pkt->dispfb2;
    p->fA0 = 1;

    p->pkt->pmode1 |= mask;
    p->pkt->pmode2 |= mask;
    p->fE0 = picA->f5C;
    p->fE4 = picA->f60;
    p->fC8 = picA->f44;
    p->fCC = picB->f48;
    p->fD4 = picA->f50;
    p->fD8 = picB->f54;

    fOk = FCheckFrameSize(p, pic1);
    if (fOk && pic1->f28 == 1 && pic2->f28 == 1) {
        pic1->f10 *= 2;
        if (p->fC4 != 0)
            func_0024C670(p, pic1);
        else
            func_0024B9F0(p, pic1);
        pic1->f10 >>= 1;
        if (p->f8 != 2) {
            p->f8 = 2;
            p->fC0 = p->f128;
        }
        p->f834 = 1;
    }
}
