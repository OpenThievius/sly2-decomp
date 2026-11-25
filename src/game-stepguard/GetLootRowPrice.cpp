#include "shopmenu.h"
extern "C" {
void sprintf(char *, const char *, int);
extern SHOPMENU B_003DA150;
extern LOOTROW D_002C3288[];
extern const char RO_002A79A0[];

void GetLootRowPrice(char *out, int row) {
    unsigned int kind = B_003DA150.arow[B_003DA150.ifirst + row].id;
    int price = 0;
    if (kind < 0x40U) {
        price = D_002C3288[kind].price;
    }
    if (price != 0) {
        sprintf(out, RO_002A79A0, price);
        return;
    }
    *out = 0;
}
}
