#include "sly2.h"
#include "shopmenu.h"
#include "blot.h"
extern "C" {
void SwitchBlotLabel(BLOT *, int, void *);
int ShopMenu_IrowEnd(SHOPMENU *);
void func_00213928(BLOT *, int);
void func_00213A08(BLOT *, int, int);
void func_00213B00(BLOT *, int);
void func_00213BD8(BLOT *, int, int);
void func_00213CD8(BLOT *, int, void *);
extern int B_003DA570;
extern GADGETDEF D_002BCD00[];
extern int D_002C3588[];
extern float RO_002C35B0;
}
void ShopMenu_UpdateBlot(SHOPMENU *menu)
{
    if (menu->pblot->blots != 2) return;
    float vec[8] __attribute__((aligned(16)));
    memset(vec, 0, 0x20);
    vec[3] = 1.0f;
    vec[0] = 1.0f;
    int irowEnd = ShopMenu_IrowEnd(menu);
    if (menu->ifirst > 0) {
        int label = menu->mode == 0 ? 0x4DA : 0x4A1;
        if (B_003DA570) {
            func_00213CD8(menu->pblot, label, vec);
            vec[5] += RO_002C35B0;
        }
        SwitchBlotLabel(menu->pblot, label, &menu->labelUp);
    } else {
        SwitchBlotLabel(menu->pblot, -1, &menu->labelUp);
    }
    int irow = menu->ifirst;
    if (irow < irowEnd) {
        // addu operand order: retail adds the offset first; the typed &menu->arow[irow] scores 1, this form scores 0
        SHOPROW *prow = (SHOPROW *)(irow * 8 + (sptr)menu->arow);
        do {
            int oid = D_002C3588[irow - menu->ifirst];
            switch (menu->mode) {
            case 0:
                if (prow->id != -1) {
                    switch (D_002BCD00[prow->id].type) {
                    case 7: prow->label = 0x456; break;
                    case 9: prow->label = 0x458; break;
                    case 8: prow->label = 0x457; break;
                    }
                    func_00213BD8(menu->pblot, 0x455, oid);
                    func_00213BD8(menu->pblot, prow->label, oid);
                } else {
                    func_00213A08(menu->pblot, 0x455, oid);
                    func_00213A08(menu->pblot, prow->label, oid);
                    prow->label = -1;
                }
                break;
            case 1:
                if (prow->id != -1) func_00213BD8(menu->pblot, 0x455, oid);
                else func_00213A08(menu->pblot, 0x455, oid);
                break;
            }
            irow++;
            prow++;
        } while (irow < irowEnd);
    }
    if (menu->isel >= 0) {
        func_00213B00(menu->pblot, 0x437);
        memset(vec, 0, 0x20);
        vec[5] = RO_002C35B0 * (float)(menu->isel - menu->ifirst);
        vec[3] = 1.0f;
        vec[0] = 1.0f;
        func_00213CD8(menu->pblot, 0x437, vec);
    } else {
        func_00213928(menu->pblot, 0x437);
    }
    if (irowEnd < menu->count) {
        int label = menu->mode == 0 ? 0x4DD : 0x4A4;
        if (B_003DA570) {
            func_00213CD8(menu->pblot, label, vec);
            vec[5] += RO_002C35B0;
        }
        SwitchBlotLabel(menu->pblot, label, &menu->labelDown);
    } else {
        SwitchBlotLabel(menu->pblot, -1, &menu->labelDown);
    }
    SwitchBlotLabel(menu->pblot, menu->dialogKind != -1 ? 0x43B : 0x439, &menu->labelDialog);
}
// x
