#include "sly2.h"
/* the globset an SO embeds at 0x80; GLOBSET::GLOBSET (0x167310) constructs it */
struct GLOBSET { char unknown_0x0[0x4C]; int field_0x4C; };
struct SUB { int a; int b; int c; void *vptr; };
/* the words of a guard (STEPGUARD, 0x1010 bytes) that its inlined constructor chain stores, vtable pointers included */
struct GUARDINIT { int f0; int f4; int f8; void *vptr; char pad0[0x70]; GLOBSET globset; char pad1[0x174 - 0xD0]; int f174; char pad2[0xDB0 - 0x178]; char jumper[0x70]; SUB sub; };
extern "C" char D_002D9978[], D_002CB1F0[], D_002DA568[], D_002DA9D0[];
extern "C" int __7GLOBSET(GLOBSET *);
extern "C" int InitJumper(void *);

extern "C" GUARDINIT *ConstructGuard(GUARDINIT *pguard)
{
    void *vptrSub = D_002CB1F0;
    pguard->f0 = 0;
    pguard->f4 = 0;
    pguard->vptr = D_002D9978;
    __7GLOBSET(&pguard->globset);
    pguard->f174 = 0;
    pguard->vptr = D_002DA568;
    InitJumper(pguard->jumper);
    SUB *psub = &pguard->sub;
    psub->vptr = vptrSub;
    pguard->sub.a = 0;
    pguard->sub.b = 0;
    psub->vptr = D_002DA9D0;
    return pguard;
}
