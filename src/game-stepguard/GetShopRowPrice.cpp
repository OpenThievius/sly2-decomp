// SPDX-License-Identifier: GPL-3.0-or-later
#include "shopmenu.h"
extern SHOPMENU B_003DA150;
extern GADGETDEF D_002BCD00[];
extern const char RO_002A79A0[];
extern "C" int sprintf(char *, const char *, ...);
extern "C" void GetShopRowPrice(char *out, int row)
{
    unsigned itemId = B_003DA150.arow[B_003DA150.ifirst + row].id;
    int price = 0;
    if (itemId < 0x2B)
        price = D_002BCD00[itemId].price;
    if (price != 0)
        sprintf(out, RO_002A79A0, price);
    else
        *out = 0;
}
