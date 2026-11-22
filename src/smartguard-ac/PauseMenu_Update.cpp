// SPDX-License-Identifier: GPL-3.0-or-later
#include "cref.h"
#include "pausemenu.h"
struct SAVE { u8 unknown_0x0[0x5464]; };
extern "C" {
int FBlotLabelPlaying(PAUSEBLOT *, int);
int FJoyButtonPressed(void *, int);
void MemcardMenu_SetState(void *, int);
void PauseMenu_AdjustOption(PAUSEMENU *, PAUSEPAGE *, PAUSEITEM *);
void PauseMenu_ApplyOption(PAUSEMENU *, PAUSEITEM *);
void PauseMenu_CancelOption(PAUSEMENU *, PAUSEITEM *);
void PauseMenu_Close(PAUSEMENU *);
void PauseMenu_Pop(PAUSEMENU *);
void PauseMenu_SetState(PAUSEMENU *, int);
CRef RefGetGameSaveValue(int, SAVE *);
int UpdateJoyNavY(void *);
void func_001AF490(PAUSEMENU *);
int func_001B0078(PAUSEMENU *);
void func_001D9870();
extern char B_002E6550[];
struct MCDATA { SAVE asave[3]; };
/* the memory card menu's block at 0x7FDC of the same object: its selected slot is 0x7D58 into it */
struct MCCARD { u8 unknown_0x0[0x7D58]; SAVE *psaveSelected; };
extern union { MCDATA slots; struct { u8 unknown_0x0[0x7FDC]; MCCARD card; } block; } B_002E6604;
extern int B_003E0FAC;
}

extern "C" void PauseMenu_Update(PAUSEMENU *pmenu)
{
    func_001D9870();
    if (pmenu->depth > 0) {
        PAUSEPAGE *ppage = &pmenu->apage[pmenu->depth - 1];
        for (int iitem = 0; iitem < ppage->citem; iitem++) {
            PAUSEITEM *pitem = &ppage->aitem[iitem];
            if (pitem->pfnUpdate != 0)
                pitem->pfnUpdate(pitem);
        }
        switch (pmenu->state) {
        case 0:
            break;
        case 1:
            if (!FBlotLabelPlaying(ppage->pblot, 0x314)) {
                if (pmenu->depthNext != -1) {
                    pmenu->depth = pmenu->depthNext;
                    pmenu->depthNext = -1;
                }
                PauseMenu_SetState(pmenu, 7);
            }
            break;
        case 2:
            if (!FBlotLabelPlaying(ppage->pblot, 0x314)) {
                if (pmenu->depthNext != -1)
                    pmenu->depthNext = -1;
                else
                    pmenu->depth--;
                if (pmenu->depth == 0) {
                    PAUSEBLOT *pblot = ppage->pblot;
                    pblot->vt->pfnHide((char *)pblot + pblot->vt->deltaHide);
                    PauseMenu_SetState(pmenu, 0);
                } else {
                    PauseMenu_SetState(pmenu, 7);
                }
            }
            break;
        case 3:
            if (!FBlotLabelPlaying(ppage->pblot, ppage->plabels->labelBack)) {
                pmenu->depth = pmenu->depthNext;
                pmenu->depthNext = -1;
                PauseMenu_SetState(pmenu, 4);
            }
            break;
        case 4:
            if (!FBlotLabelPlaying(ppage->pblot, ppage->plabels->labelEnter))
                PauseMenu_SetState(pmenu, 7);
            break;
        case 8:
            if (!FBlotLabelPlaying(ppage->pblot, 0x314)) {
                PAUSEBLOT *pblot = ppage->pblot;
                pblot->vt->pfnHide((char *)pblot + pblot->vt->deltaHide);
                PauseMenu_SetState(pmenu, 0);
            }
            break;
        case 5:
            if (!FBlotLabelPlaying(ppage->pblot, ppage->plabels->labelUp)) {
                PauseMenu_SetState(pmenu, 7);
                if (pmenu->pjoy != 0) {
                    int dy = UpdateJoyNavY(pmenu->pjoy);
                    if (dy < 0)
                        PauseMenu_SetState(pmenu, 6);
                    else if (dy > 0)
                        PauseMenu_SetState(pmenu, 5);
                }
            }
            break;
        case 6:
            if (!FBlotLabelPlaying(ppage->pblot, ppage->plabels->labelDown)) {
                PauseMenu_SetState(pmenu, 7);
                if (pmenu->pjoy != 0) {
                    int dy = UpdateJoyNavY(pmenu->pjoy);
                    if (dy < 0)
                        PauseMenu_SetState(pmenu, 6);
                    else if (dy > 0)
                        PauseMenu_SetState(pmenu, 5);
                }
            }
            break;
        case 7:
            if (pmenu->pjoy != 0) {
                int grfbtn = FJoyButtonPressed(pmenu->pjoy, 0x870);
                if (grfbtn & 0x800) {
                    PauseMenu_Close(pmenu);
                } else if ((grfbtn & 0x10) || (ppage->citem == 0 && grfbtn != 0)) {
                    if (ppage->fSub != 0)
                        func_001AF490(pmenu);
                    else
                        PauseMenu_Pop(pmenu);
                } else if (pmenu->depth > 0 && (grfbtn & 0x40)) {
                    PAUSEITEM *pitem = &ppage->aitem[ppage->iitemCur];
                    if (pitem->pfnActivate != 0)
                        pitem->pfnActivate(pitem);
                    if (!(pitem->grf & 2)) {
                        if (pitem->grf & 1) {
                            if (ppage->fSub != 0)
                                func_001AF490(pmenu);
                            else
                                PauseMenu_Pop(pmenu);
                        } else {
                            PauseMenu_Close(pmenu);
                        }
                    }
                } else if (grfbtn & 0x20) {
                    int kind = func_001B0078(pmenu);
                    if (kind == 0x19 || kind == 0x1E) {
                        SAVE *psave = &B_002E6604.slots.asave[ppage->iitemCur];
                        float value = RefGetGameSaveValue(B_003E0FAC, psave).m_tag.m_g;
                        if (value != 0.0f) {
                            MCCARD *pcard = &B_002E6604.block.card;
                            pcard->psaveSelected = psave;
                            MemcardMenu_SetState(B_002E6550, 0x20);
                        }
                    }
                } else if (ppage != 0) {
                    int dy = UpdateJoyNavY(pmenu->pjoy);
                    if (dy < 0)
                        PauseMenu_SetState(pmenu, 6);
                    else if (dy > 0)
                        PauseMenu_SetState(pmenu, 5);
                }
            }
            break;
        case 11:
            if (!FBlotLabelPlaying(ppage->pblot, 0x331))
                PauseMenu_SetState(pmenu, 10);
            break;
        case 9:
            if (!FBlotLabelPlaying(ppage->pblot, 0x332))
                PauseMenu_SetState(pmenu, 7);
            break;
        case 10:
            if (pmenu->pjoy != 0) {
                PAUSEITEM *pitem = &ppage->aitem[ppage->iitemCur];
                int grfbtn = FJoyButtonPressed(pmenu->pjoy, 0x850);
                if (grfbtn & 0x800) {
                    PauseMenu_CancelOption(pmenu, pitem);
                    PauseMenu_Close(pmenu);
                } else if (grfbtn & 0x10) {
                    PauseMenu_CancelOption(pmenu, pitem);
                } else if (grfbtn & 0x40) {
                    PauseMenu_ApplyOption(pmenu, pitem);
                } else {
                    PauseMenu_AdjustOption(pmenu, ppage, pitem);
                }
            }
            break;
        }
    }
}
