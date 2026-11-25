/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The SDK-range vector object and its listeners (src/sdk: Vector_Add, Vector_Clear, Vector_NotifyAdd), as the three functions read
   them. A CVECTOR derives from a base that has 0xC bytes of fields and the virtuals (vtable pointer at 0xC, as BASIC's layout in lo.h; its own fields cannot sit in that class, g++ 2.95 would put the vtable pointer after them), a CARY (the
   array's buffer and its count: func_00116E30 grows it, func_00116D28 empties the 0x18 bytes from 0x10) and the head of a list of
   listeners at 0x28. A listener keeps its next at 0x4 and its vtable pointer at 0x8. Slot numbers are the vtable offsets 8 * n the
   retail calls use. C++ only. */
#ifndef SLY2_CVECTOR_H
#define SLY2_CVECTOR_H
struct CARY {
    int *pb;
    int c;
};

struct VECTORLISTENER {
    unsigned char unknown_0x0[4];
    VECTORLISTENER *pnext;       /* Vector_Clear, Vector_NotifyAdd walk it */
    virtual void OnClear();      /* 1: Vector_Clear calls it on each listener, without arguments */
    virtual void OnAdd(int iitem); /* 2: Vector_NotifyAdd passes its second argument */
};

struct CVECTORBASE {
    unsigned char unknown_0x0[0xC];
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void OnAdd(int *pitem); /* 6: Vector_Add passes the address of the item it appended */
};

struct CVECTOR : CVECTORBASE {
    /* 0x10 */ CARY ary;
    unsigned char unknown_0x18[0x10];
    /* 0x28 */ VECTORLISTENER *plistener;
};
#endif
