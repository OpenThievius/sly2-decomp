// SPDX-License-Identifier: GPL-3.0-or-later
#include "jobmenu.h"
struct TASKFRAME { int frame; int count; TASK **tasks; };
extern "C" {
int CStackFrame_Construct(void *);
void CStackFrame_Destructor(void *, int);
void JobMenu_Select(JOBMENU *, int);
void OrderTasks(int *, TASK ***);
int func_00163430(JOB *);
void func_00213928(BLOT *, int);
void *memmove(void *, const void *, unsigned int);
void *memset(void *, int, u64);
void qsort(void *, int, u64, int (*)(const void *, const void *));
int func_00165C28(const void *, const void *);
}
extern "C" void JobMenu_BuildList(JOBMENU *menu)
{
    TASKFRAME local;
    for (int index = 0; index < menu->cent; index++) {
        JOBROW *item = &menu->aent[index];
        if (item->label != -1) {
            func_00213928(menu->pblot, item->label);
            item->label = -1;
        }
        if (item->labelDone != -1) {
            func_00213928(menu->pblot, item->labelDone);
            item->labelDone = -1;
        }
    }
    menu->isel = 0;
    menu->cent = 0;
    memset(menu->aent, 0, 0);
    CStackFrame_Construct(&local);
    OrderTasks(&local.count, &local.tasks);
    qsort(local.tasks, local.count, 4, func_00165C28);
    switch (menu->page) {
    case 0: {
        JOB *previous = 0;
        for (int index = 0; index < local.count; index++) {
            JOB *owner = local.tasks[index]->job;
            if (owner != 0 && previous != owner) {
                previous = owner;
                if (func_00163430(owner) > 0 && owner->field_0x6C != -1) {
                    JOBROW *item = &menu->aent[menu->cent];
                    menu->cent++;
                    item->pjob = owner;
                    item->labelDone = -1;
                    item->label = -1;
                    if (menu->pjobSel == owner)
                        menu->isel = item - menu->aent;
                }
            }
        }
        break;
    }
    case 1: {
        int seen = 0;
        for (int index = 0; index < local.count; index++) {
            TASK *task = local.tasks[index];
            if (menu->pjobSel == task->job && task->labelId != -1) {
                if (seen != 0 && task->state == 0)
                    break;
                JOBROW *item = &menu->aent[menu->cent++];
                item->labelDone = -1;
                item->label = -1;
                item->ptask = task;
                int flag = task->state;
                if (flag == 1)
                    seen = 1;
                if (flag == 0)
                    break;
            }
        }
        break;
    }
    }
    int count = menu->cent;
    int keep = menu->crowMax;
    if (count > keep) {
        memmove(menu->aent, &menu->aent[count - keep], keep * 12);
        int dropped = menu->cent - menu->crowMax;
        if (dropped < menu->isel)
            menu->isel = menu->isel - dropped;
        else
            menu->isel = 0;
        menu->cent = menu->crowMax;
    }
    JobMenu_Select(menu, menu->isel);
    CStackFrame_Destructor(&local, 2);
}
