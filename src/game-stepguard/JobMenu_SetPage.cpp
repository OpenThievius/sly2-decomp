#include "sly2.h"
#include "sw.h"
#include "jobmenu.h"
#include "blot.h"
#include "clock.h"
extern SW B_003DD490;
extern "C" {
extern JOB *B_003E0F9C;
void SetHandsOff(void *, int);
void ClearHandsOff(void *, int);
void SetBlotBlots(BLOT *, int);
void SetTimerTimers__FP5TIMER6TIMERS(BLOT *, int);
void JobMenu_BuildList(JOBMENU *);
void JobMenu_SetPage(JOBMENU *menu, int page)
{
    int pageNew = page;
    if (!menu->pblot)
        pageNew = -1;
    if (pageNew == menu->page)
        return;
    if (menu->page == -1) {
        SetHandsOff(&B_003DD490, 0);
        menu->Slot10();
    }
    int pagePrev = menu->page;
    menu->page = pageNew;
    menu->tPage = g_2dded0.tReal;
    switch (pageNew) {
    case -1:
        ClearHandsOff(&B_003DD490, 0);
        menu->Slot11();
        if (menu->pblot->blots > 0)
            SetTimerTimers__FP5TIMER6TIMERS(menu->pblot, 1);
        menu->labelHolder2 = menu->labelHolder1 = menu->labelHolder0 = -1;
        break;
    case 0:
        menu->crowMax = 10;
        menu->pblot->labelVisible = 0x4E3;
        menu->pblot->labelDisappear = 0x4E2;
        if (pagePrev == 1)
            menu->pblot->labelAppear = 0x4E8;
        else
            menu->pblot->labelAppear = 0x4E1;
        if (menu->pblot->blots != 0) {
            SetBlotBlots(menu->pblot, 1);
            SetTimerTimers__FP5TIMER6TIMERS(menu->pblot, 2);
            menu->pblot->Update();
        }
        break;
    case 1:
        if (menu->isel >= 0 && menu->isel < menu->cent)
            menu->pjobSel = menu->aent[menu->isel].pjob;
        else
            menu->pjobSel = B_003E0F9C;
        menu->fFromJobs = pagePrev == 0;
        menu->crowMax = 4;
        menu->pblot->labelVisible = 0x4E6;
        menu->pblot->labelDisappear = 0x4E5;
        if (pagePrev == 0)
            menu->pblot->labelAppear = 0x4E7;
        else
            menu->pblot->labelAppear = 0x4E4;
        if (menu->pblot->blots != 0) {
            SetBlotBlots(menu->pblot, 1);
            SetTimerTimers__FP5TIMER6TIMERS(menu->pblot, 2);
            menu->pblot->Update();
        }
        break;
    }
    JobMenu_BuildList(menu);
    menu->Slot14(-1);
}
}
