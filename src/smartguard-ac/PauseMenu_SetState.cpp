// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "pausemenu.h"
struct GsDisplay { u32 dx : 12; u32 dy : 11; u32 magh : 4; u32 magv : 2; u32 pad0 : 3; u32 dw : 12; u32 dh : 11; u32 pad1 : 9; };
struct DISPENV { u64 pmode; u64 smode2; u64 dispfb; GsDisplay display; u64 bgcolor; };
extern DISPENV B_002DEB80[2];
extern float B_002F6468, B_002F646C, B_003DD18C, B_003DD190;
extern "C" {
void func_00213B00(PAUSEBLOT *, int);
void SeekBlotLabel(float u, PAUSEBLOT *pblot, int label);
}
extern "C" void PauseMenu_SetState(PAUSEMENU *pmenu, unsigned state)
{
    unsigned stateOld = pmenu->state;
    if (stateOld == state)
        return;
    int depth = pmenu->depth;
    PAUSEPAGE *ppage = 0;
    if (depth > 0)
        ppage = &pmenu->apage[depth - 1];
    switch (stateOld) {
    case 5:
        if (ppage) {
            int iitemNext = ppage->iitemCur + 1;
            ppage->iitemCur = iitemNext;
            if (iitemNext >= ppage->citem)
                ppage->iitemCur = 0;
        }
        break;
    case 6:
        if (ppage) {
            int iitemPrev = ppage->iitemCur - 1;
            ppage->iitemCur = iitemPrev;
            if (iitemPrev < 0)
                ppage->iitemCur = ppage->citem - 1;
        }
        break;
    case 0:
        pmenu->vt->pfnLeave((char *)pmenu + pmenu->vt->deltaLeave);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    default:
        break;
    }
    pmenu->state = state;
    if (state < 12) {
        switch (state) {
        case 1:
            if (ppage && ppage->pblot) {
                ppage->pblot->vt->pfnSelect((char *)ppage->pblot + ppage->pblot->vt->deltaSelect, ppage->plabels->selEnter);
                func_00213B00(ppage->pblot, ppage->plabels->labelEnter);
            }
            break;
        case 3:
            if (ppage && ppage->pblot)
                func_00213B00(ppage->pblot, ppage->plabels->labelBack);
            break;
        case 4:
            if (ppage && ppage->pblot)
                func_00213B00(ppage->pblot, ppage->plabels->labelEnter);
            break;
        case 2:
        case 8:
            if (ppage && ppage->pblot) {
                ppage->pblot->vt->pfnSelect((char *)ppage->pblot + ppage->pblot->vt->deltaSelect, ppage->plabels->selBack);
                func_00213B00(ppage->pblot, ppage->plabels->labelBack);
            }
            break;
        case 5:
            if (ppage && ppage->pblot)
                func_00213B00(ppage->pblot, ppage->plabels->labelUp);
            break;
        case 6:
            if (ppage && ppage->pblot)
                func_00213B00(ppage->pblot, ppage->plabels->labelDown);
            break;
        case 11:
            if (ppage && ppage->pblot)
                func_00213B00(ppage->pblot, 0x331);
            break;
        case 9:
            if (ppage && ppage->pblot)
                func_00213B00(ppage->pblot, 0x332);
            break;
        case 10:
            if (ppage && ppage->pblot) {
                PAUSEITEM *pitem = &ppage->aitem[ppage->iitemCur];
                switch (pitem->kind) {
                case 0x67:
                    func_00213B00(ppage->pblot, 0x333);
                    func_00213B00(ppage->pblot, 0x315);
                    SeekBlotLabel(B_003DD190, ppage->pblot, 0x315);
                    break;
                case 0x68:
                    func_00213B00(ppage->pblot, 0x334);
                    func_00213B00(ppage->pblot, 0x315);
                    SeekBlotLabel(B_003DD18C, ppage->pblot, 0x315);
                    break;
                case 0x3F:
                    func_00213B00(ppage->pblot, 0x335);
                    B_002F6468 = (float)(unsigned)B_002DEB80[0].display.dx;
                    B_002F646C = (float)(unsigned)B_002DEB80[0].display.dy;
                    break;
                }
            }
            break;
        case 7:
            if (ppage && ppage->pblot) {
                ppage->pblot->vt->pfnSelect((char *)ppage->pblot + ppage->pblot->vt->deltaSelect, ppage->plabels->selIdle);
                func_00213B00(ppage->pblot, ppage->plabels->labelIdle);
            }
            break;
        case 0:
            pmenu->vt->pfnEnter((char *)pmenu + pmenu->vt->deltaEnter);
            break;
        }
    }
}
