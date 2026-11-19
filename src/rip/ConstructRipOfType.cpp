// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"

struct RIP {
    int ript;
    char pad4[0xE8];
    void **pvtrip;
};

extern void *D_002D7468[20];
extern void *D_002D74B8[20];
extern void *D_002D7508[20];
extern void *D_002D7558[20];
extern void *D_002D75A8[20];
extern void *D_002D75F8[20];
extern void *D_002D7648[20];
extern void *D_002D7698[20];
extern void *D_002D76E8[20];
extern void *D_002D7738[20];
extern void *D_002D7788[20];

extern "C" RIP *ConstructRipOfType(void *pv, int ript)
{
    RIP *prip;

    switch (ript) {
    case 3:
        memset(pv, 0, 0x100);
        ((RIP *)pv)->pvtrip = D_002D7738;
        prip = (RIP *)pv;
        break;
    case 10:
        memset(pv, 0, 0x100);
        ((RIP *)pv)->pvtrip = D_002D76E8;
        prip = (RIP *)pv;
        break;
    case 8:
        memset(pv, 0, 0x100);
        ((RIP *)pv)->pvtrip = D_002D7698;
        prip = (RIP *)pv;
        break;
    case 6:
        memset(pv, 0, 0x110);
        ((RIP *)pv)->pvtrip = D_002D7648;
        prip = (RIP *)pv;
        break;
    case 4:
        memset(pv, 0, 0x100);
        ((RIP *)pv)->pvtrip = D_002D75F8;
        prip = (RIP *)pv;
        break;
    case 9:
        memset(pv, 0, 0x110);
        ((RIP *)pv)->pvtrip = D_002D75A8;
        prip = (RIP *)pv;
        break;
    case 5:
        memset(pv, 0, 0xF0);
        ((RIP *)pv)->pvtrip = D_002D74B8;
        prip = (RIP *)pv;
        break;
    case 1:
        memset(pv, 0, 0x100);
        ((RIP *)pv)->pvtrip = D_002D7558;
        prip = (RIP *)pv;
        break;
    case 0:
        memset(pv, 0, 0xF0);
        ((RIP *)pv)->pvtrip = D_002D7508;
        prip = (RIP *)pv;
        break;
    case 7:
        memset(pv, 0, 0xF0);
        ((RIP *)pv)->pvtrip = D_002D7788;
        prip = (RIP *)pv;
        break;
    case 2:
        memset(pv, 0, 0x100);
        ((RIP *)pv)->pvtrip = D_002D7468;
        prip = (RIP *)pv;
        break;
    }
    prip->ript = ript;
    return prip;
}
