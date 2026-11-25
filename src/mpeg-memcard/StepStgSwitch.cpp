// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "stgswitch.h"
struct SW;
extern "C" {
LO *PloFindSwObject_thunk(SW *, int, int, void *);
void func_001F6978(STGSWITCH *, int);
void func_001F69F8(STGSWITCH *, int);
void func_001F6AC8(STGSWITCH *, int);
void func_001F6B48(STGSWITCH *, int);
extern SW B_003DD490;
void StepStgSwitch(STGSWITCH *sw, int id)
{
    int target = sw->istage;
    if (id == 0x609) {
        target = 0;
    } else if (id == 0x60A) {
        target = sw->cstage;
    } else if (id != -1) {
        for (int index = 0; index < sw->cstage; index++) {
            if (sw->anode[index].id == id) {
                target = index;
                break;
            }
        }
    }
    int forward = sw->istage;
    if (forward != target) {
        if (forward < target) {
            do {
                sw->istage = forward + 1;
                STGNODE *node = &sw->anode[forward];
                for (int index = 0; index < node->count; index++) {
                    STGENT *ent = &node->aent[index];
                    LO *obj = 0;
                    if ((0xC3 >> ent->kind) & 1) {
                        obj = PloFindSwObject_thunk(&B_003DD490, 1, ent->arg, sw);
                        if (obj == 0)
                            continue;
                    }
                    switch (ent->kind) {
                    case 0: obj->Add(); break;
                    case 1: obj->Remove(); break;
                    case 2: func_001F6978(sw, ent->arg); break;
                    case 3: func_001F69F8(sw, ent->arg); break;
                    case 4: func_001F6AC8(sw, ent->arg); break;
                    case 5: func_001F6B48(sw, ent->arg); break;
                    }
                }
                forward = sw->istage;
            } while (forward < target);
        } else if (target < forward) {
            do {
                sw->istage = sw->istage - 1;
                STGNODE *node = &sw->anode[sw->istage];
                int index = node->count;
                while (index-- > 0) {
                    STGENT *ent = &node->aent[index];
                    LO *obj = 0;
                    if ((0xC3 >> ent->kind) & 1) {
                        obj = PloFindSwObject_thunk(&B_003DD490, 1, ent->arg, sw);
                        if (obj == 0)
                            continue;
                    }
                    switch (ent->kind) {
                    case 0: obj->Remove(); break;
                    case 1: obj->Add(); break;
                    case 2: func_001F69F8(sw, ent->arg); break;
                    case 3: func_001F6978(sw, ent->arg); break;
                    case 4: func_001F6B48(sw, ent->arg); break;
                    case 5: func_001F6AC8(sw, ent->arg); break;
                    }
                }
            } while (target < sw->istage);
        }
        sw->fPending = 0;
    }
}
}
