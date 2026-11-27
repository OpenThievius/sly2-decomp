// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goal.h"
/* the goal: its value at 0x3C (one reader: a local view) */
struct Obj_17CDB8 : GOAL { u8 unknown_0x30[0xC]; float value; };
extern "C" {
float SMaxCrv(void *);
float SMinCrv(void *);
void func_0017CD00(Obj_17CDB8 *, int);
void func_0017CDB8(Obj_17CDB8 *obj, int useMax) {
    void *curve = ((STEPGUARD *)obj->pstep)->ptargetPath;
    if (useMax != 0) {
        obj->value = SMaxCrv(curve);
    } else {
        obj->value = SMinCrv(curve);
    }
    STEPGUARD *owner = (STEPGUARD *)obj->pstep;
    owner->nPath = owner->sPath < obj->value;
    func_0017CD00(obj, 0);
}
}
