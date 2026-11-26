/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "goal.h"
#include "stepguard.h"
#include "goals.h"
#include "asega.h"

extern "C" {
int FCanSetGuardMode(STEPGUARD *, int);
GOAL *func_00205458(STEPGUARD *, int);
ASEGA *func_00209518(void *);
void SetAsegaMasterSpeed(ASEGA *, f32);
void RemoveGuardPriorityClass(STEPGUARD *, int);
void AddGuardPriorityClass(STEPGUARD *, int);
void func_00206E50(STEPGUARD *);
void func_00206DB0(STEPGUARD *);
void func_0012D108(void *, QW);
void *PpoSwFocusBase(void *);
void SetGuardMode(STEPGUARD *pguard, int mode);
void GoalBrain_ChooseNextCommand(GOALBRAIN *);
extern char B_003DD490[];
struct CLOCK { f32 t; f32 dt; };
extern CLOCK g_2dded0;
extern QW RO_002A2DE0;
extern QW D_002C3D30;
}

void SetGuardMode(STEPGUARD *pguard, int mode)
{
    if (mode == pguard->mode) return;
    if (!FCanSetGuardMode(pguard, mode)) return;

    int modeOld = pguard->mode;
    pguard->mode = mode;
    pguard->tMode = g_2dded0.t;

    switch (modeOld) {
    case 8:
    case 13:
        if (pguard->field_0xFC4 != 0) {
            func_0012D108(pguard->field_0xFC4, RO_002A2DE0);
        }
        break;
    case 34:
    case 37:
        RemoveGuardPriorityClass(pguard, 0x38);
        func_00206E50(pguard);
        break;
    case 14: {
        GOALANIM *pgoal = (GOALANIM *)func_00205458(pguard, 0x9D);
        if (pgoal != 0) {
            ASEGA *pasega = func_00209518(pgoal->panimref);
            if (pasega != 0) {
                SetAsegaMasterSpeed(pasega, pasega->paseg->svtMaster);
            }
        }
        break;
    }
    case 21: {
        GOALBRAIN *pgoal = (GOALBRAIN *)func_00205458(pguard, 0x9C);
        if (pgoal != 0 && pgoal->cmd.type == 0x12 && (void *)pgoal->cmd.args.arg == PpoSwFocusBase(B_003DD490) &&
            pgoal->cmd.args.argf == 3.4028235e38f) {
            GoalBrain_ChooseNextCommand(pgoal);
        }
        break;
    }
    }

    switch (mode) {
    case 8:
    case 13:
        if (pguard->field_0xFC4 != 0) {
            func_0012D108(pguard->field_0xFC4, D_002C3D30);
        }
        break;
    case 34:
    case 37:
        AddGuardPriorityClass(pguard, 0x38);
        func_00206DB0(pguard);
        break;
    case 14: {
        GOALANIM *pgoal = (GOALANIM *)func_00205458(pguard, 0x9D);
        if (pgoal != 0) {
            ASEGA *pasega = func_00209518(pgoal->panimref);
            if (pasega != 0) {
                SetAsegaMasterSpeed(pasega, 0.0f);
            }
        }
        f32 *pvel = (f32 *)&pguard->velGoal;
        pvel[2] = 0.0f;
        pvel[1] = 0.0f;
        ((f32 *)&pguard->velGoal)[0] = 0.0f;
        break;
    }
    case 21: {
        GOALBRAIN *pgoal = (GOALBRAIN *)func_00205458(pguard, 0x9C);
        if (pgoal != 0) {
            switch (pgoal->cmd.type) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 12:
            case 16:
            case 17:
            case 18:
                GoalBrain_ChooseNextCommand(pgoal);
                break;
            }
        }
        break;
    }
    }
}
