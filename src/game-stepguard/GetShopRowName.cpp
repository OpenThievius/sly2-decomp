// SPDX-License-Identifier: GPL-3.0-or-later
#include "shopmenu.h"
extern SHOPMENU B_003DA150;
extern GADGETDEF D_002BCD00[];
extern char B_003DD490[];
extern "C" char *PchzStringFromId__FP2SWi(void *, int);
extern "C" char *strcpy(char *, const char *);
void GetShopRowName(char *out, int row)
{
    SHOPMENU *shop = &B_003DA150;
    unsigned gadget = shop->arow[B_003DA150.ifirst + row].id;
    int sid = -1;
    if (gadget < 0x2B)
        sid = D_002BCD00[gadget].sidName;
    if (sid != -1)
        strcpy(out, PchzStringFromId__FP2SWi(B_003DD490, sid));
    else
        out[0] = 0;
}
