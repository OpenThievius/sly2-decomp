// SPDX-License-Identifier: GPL-3.0-or-later
struct TASKINFO { char pad0[0x54]; int flag; char pad1[0x5C - 0x58]; int link; char pad2[0x6C - 0x60]; int ready; char pad3[0x7C - 0x70]; TASKINFO *owner; };
struct ITEM { TASKINFO *task; int first; int second; };
struct JOBMENU {
    char pad0[0x24]; int pool; char pad1[0x40 - 0x28]; int mode; char pad2[0x48 - 0x44];
    int count; ITEM items[1]; char pad3[0x10C - 0x58]; int keep; TASKINFO *current; char pad4[0x118 - 0x114]; int selected;
};
struct TASKFRAME { int frame; int count; TASKINFO **tasks; };
extern "C" {
int CStackFrame_Construct(void *);
void CStackFrame_Destructor(void *, int);
void JobMenu_Select(JOBMENU *, int);
void OrderTasks(int *, TASKINFO ***);
int func_00163430(TASKINFO *);
void func_00213928(int, int);
void *memmove(void *, const void *, unsigned long);
void *memset(void *, int, unsigned long);
void qsort(void *, int, unsigned long, int (*)(const void *, const void *));
int func_00165C28(const void *, const void *);
}
extern "C" void JobMenu_BuildList(JOBMENU *menu)
{
    TASKFRAME local;
    for (int index = 0; index < menu->count; index++) {
        ITEM *item = &menu->items[index];
        if (item->first != -1) {
            func_00213928(menu->pool, item->first);
            item->first = -1;
        }
        if (item->second != -1) {
            func_00213928(menu->pool, item->second);
            item->second = -1;
        }
    }
    menu->selected = 0;
    menu->count = 0;
    memset(menu->items, 0, 0);
    CStackFrame_Construct(&local);
    OrderTasks(&local.count, &local.tasks);
    qsort(local.tasks, local.count, 4, func_00165C28);
    switch (menu->mode) {
    case 0: {
        TASKINFO *previous = 0;
        for (int index = 0; index < local.count; index++) {
            TASKINFO *owner = local.tasks[index]->owner;
            if (owner != 0 && previous != owner) {
                previous = owner;
                if (func_00163430(owner) > 0 && owner->ready != -1) {
                    ITEM *item = &menu->items[menu->count++];
                    item->first = -1;
                    item->task = owner;
                    item->second = -1;
                    if (menu->current == owner)
                        menu->selected = item - menu->items;
                }
            }
        }
        break;
    }
    case 1: {
        int seen = 0;
        for (int index = 0; index < local.count; index++) {
            TASKINFO *task = local.tasks[index];
            if (menu->current == task->owner && task->link != -1) {
                if (seen != 0 && task->flag == 0)
                    break;
                ITEM *item = &menu->items[menu->count++];
                item->second = -1;
                item->first = -1;
                item->task = task;
                int flag = task->flag;
                if (flag == 1)
                    seen = 1;
                if (flag == 0)
                    break;
            }
        }
        break;
    }
    }
    int count = menu->count;
    int keep = menu->keep;
    if (count > keep) {
        memmove(menu->items, &menu->items[count - keep], keep * 12);
        int dropped = menu->count - menu->keep;
        if (dropped < menu->selected)
            menu->selected = menu->selected - dropped;
        else
            menu->selected = 0;
        menu->count = menu->keep;
    }
    JobMenu_Select(menu, menu->selected);
    CStackFrame_Destructor(&local, 2);
}
