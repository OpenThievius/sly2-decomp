/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

/* A camera policy (CPLCY, 0xD0 bytes): only its vtable pointer is known here. */
struct CPLCY {
    u8 unknown_0x0[0xC];
    void *vtable;
    u8 unknown_0x10[0xC0];
};

/* The camera manager up to its last constructed member; the members are named after the init function that runs on them. */
struct CM {
    s32 unknown_0x0;
    s32 unknown_0x4;
    u8 unknown_0x8[4];
    void *vtable;
    u8 unknown_0x10[0x390];
    u8 cpman[0x10];
    u8 cptn[0xA0];
    u8 cplook[0x58];
    u8 cplcyCamobj[0x18];
    u8 unknown_0x4C0[0x40];
    u8 unknown_0x500[0x20];
    u8 unknown_0x520[0xD0];
    u8 unknown_0x5F0[0x10];
    struct CPLCY cplcy;
};

void InitCplcy(struct CPLCY *);                          /* extern */
void InitCplcyCamobj(void *);                    /* extern */
void InitCplook(void *);                         /* extern */
void InitCpman(void *);                          /* extern */
void InitCptn(void *);                           /* extern */
void func_00150728(void *);                      /* extern */
void func_00151208(void *);                      /* extern */
void func_00151610(void *);                      /* extern */
void func_001518C8(void *);                      /* extern */
extern void *D_002CA4D0[];
extern void *D_002CD378[];

struct CM *CM_Construct(struct CM *pcm) {
    struct CPLCY *pcplcy;

    pcm->unknown_0x0 = 0;
    pcplcy = &pcm->cplcy;
    pcm->unknown_0x4 = 0;
    pcm->vtable = D_002CA4D0;
    InitCpman(pcm->cpman);
    InitCptn(pcm->cptn);
    InitCplook(pcm->cplook);
    InitCplcyCamobj(pcm->cplcyCamobj);
    func_00151208(pcm->unknown_0x4C0);
    func_00151610(pcm->unknown_0x500);
    func_00150728(pcm->unknown_0x520);
    func_001518C8(pcm->unknown_0x5F0);
    InitCplcy(pcplcy);
    pcplcy->vtable = D_002CD378;
    return pcm;
}
