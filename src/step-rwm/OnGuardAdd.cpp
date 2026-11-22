// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
extern "C" {
void func_001CB518(STEPGUARD *, void *);
void GoalStack_Clear(GOALSTACK *);
void func_00209778(GUARDHEADING *);
void SetGuardGrfsgs(STEPGUARD *, u64);
void func_0020CE40(FALLCHECK *);
void func_0020D1C8(GUARDDAMAGE *);
void EnableFallCheck(FALLCHECK *);
QW PosLoWorld(STEPGUARD *);
float RadYawSo(STEPGUARD *);
void SetStepRadTarget(STEPGUARD *, float);
int GrfsgsFromSgs(int);
GUARDANIM *PguardanimBestMatch(STEPGUARD *, int);
void func_00153EF8(SENSOR *, STEPGUARD *, int);
void func_001F1A40(STEPGUARD *);
void func_001F1CF8(STEPGUARD *);
GOAL *func_00205438(STEPGUARD *, int);
void func_001A58D0(SENSOR *, STEPGUARD *, int);
extern int g_2e1e40, g_2f7900, g_2dd5bc, B_002DD648;
}
void OnGuardAdd(STEPGUARD *pguard, void *ppool)
{
    func_001CB518(pguard, ppool);
    void *pposHome = &pguard->posHome;
    pguard->field_0x33C = pguard->field_0x338;
    pguard->field_0xE88 = pguard->field_0xE84;
    pguard->field_0x344 = pguard->field_0x340;
    GoalStack_Clear(pguard->pgoalstack());
    func_00209778(&pguard->heading);
    SetGuardGrfsgs(pguard, 0);
    func_0020CE40(pguard->pfallcheck);
    func_0020D1C8(pguard->pdamage);
    EnableFallCheck(pguard->pfallcheck);
    pguard->posHome = PosLoWorld(pguard);
    pguard->radHome = RadYawSo(pguard);
    pguard->phome->pposHome = pposHome;
    pguard->phome->yaw = pguard->radHome;
    SetStepRadTarget(pguard, pguard->radHome);
    pguard->grf = 0;
    if (PguardanimBestMatch(pguard, GrfsgsFromSgs(9)))
        pguard->grf |= 2;
    else
        pguard->field_0xE78 = 2;
    if (PguardanimBestMatch(pguard, GrfsgsFromSgs(8)))
        pguard->grf |= 4;
    if (PguardanimBestMatch(pguard, GrfsgsFromSgs(0xF)))
        pguard->grf |= 1;
    if (PguardanimBestMatch(pguard, GrfsgsFromSgs(0x11)))
        pguard->grf |= 8;
    func_00153EF8(pguard->psensor, pguard, g_2e1e40);
    func_00153EF8(pguard->psensor, pguard, g_2f7900);
    func_00153EF8(pguard->psensor, pguard, g_2dd5bc);
    func_00153EF8(pguard->psensor, pguard, B_002DD648);
    if (pguard->prig) {
        func_001F1A40(pguard);
        func_001F1CF8(pguard);
    }
    if (pguard->field_0xFEC)
        pguard->field_0xFEC->Remove();
    GOAL *pgoalBrain = func_00205438(pguard, 0x9C);
    pgoalBrain->Activate();
    func_001A58D0(pguard->psensor, pguard, 0xF);
    pguard->psensor->powner = pguard;
    pguard->psensor->poxa = pguard->poxa;
}
