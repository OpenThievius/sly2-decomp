#include "shopmenu.h"
#include "blot.h"
#include "clock.h"
#include "sw.h"
extern "C" {
void SetClockRate(CLOCK *, int, float);
void SetHandsOff(void *, int);
void ClearHandsOff(void *, int);
void SetBlotBlots(BLOT *, int);
void SetTimerTimers__FP5TIMER6TIMERS(BLOT *, int);
void ShopMenu_BuildList(SHOPMENU *);
void ShopMenu_Select(SHOPMENU *, int);
void *NewEmitter(int);
void SetEmitterUnpositioned(void *, int);
extern SW B_003DD490;
}

void ShopMenu_SetPage(SHOPMENU *shop, int page)
{
    int pageNew = page;
    if (!shop->pblot)
        pageNew = -1;
    if (pageNew == shop->mode)
        return;
    if (shop->mode == -1) {
        SetClockRate(&g_2dded0, 0, 0.0f);
        SetHandsOff(&B_003DD490, 0);
        shop->Slot10();
        SetBlotBlots(shop->pblot, 1);
    }
    int pagePrev = shop->mode;
    shop->mode = pageNew;
    shop->tPage = g_2dded0.tReal;
    switch (pageNew) {
    case -1: {
        BLOT *blot = shop->pblot;
        blot->Hide();
        SetClockRate(&g_2dded0, 0, 1.0f);
        ClearHandsOff(&B_003DD490, 0);
        shop->Slot11();
        if (shop->pblot->blots > 0)
            SetTimerTimers__FP5TIMER6TIMERS(shop->pblot, 1);
        shop->labelDialog = -1;
        shop->labelUp = -1;
        shop->labelDown = -1;
        break;
    }
    case 0: {
        BLOT *blot = shop->pblot;
        blot->labelAppear = 0x4D4;
        shop->pblot->labelVisible = 0x4D5;
        shop->pblot->labelDisappear = 0x4D6;
        if (pagePrev == 1) {
            SetBlotBlots(shop->pblot, 1);
            SetBlotBlots(shop->pblot, 2);
        } else {
            SetTimerTimers__FP5TIMER6TIMERS(shop->pblot, 2);
        }
        SetEmitterUnpositioned(NewEmitter(0x35), 0);
        break;
    }
    case 1: {
        BLOT *blot = shop->pblot;
        blot->labelAppear = 0x49B;
        shop->pblot->labelVisible = 0x49C;
        shop->pblot->labelDisappear = 0x49D;
        if (pagePrev == 0) {
            SetBlotBlots(shop->pblot, 1);
            SetBlotBlots(shop->pblot, 2);
        } else {
            SetTimerTimers__FP5TIMER6TIMERS(shop->pblot, 2);
        }
        SetEmitterUnpositioned(NewEmitter(0x35), 0);
        break;
    }
    }
    ShopMenu_BuildList(shop);
    ShopMenu_Select(shop, 0);
    shop->Slot14(-1);
}
