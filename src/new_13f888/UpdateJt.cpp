/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goal.h"
#include "goals.h"
#include "jt.h"
#include "joy.h"

extern "C" {
void UpdateStep(JT *pjt, float dt);
void UpdateJtGadgets(JT *pjt);
int FButtonPressedWithin(JOY *pjoy, int grfbtn, float dt);
void func_00140338(JT *pjt);
void func_00144640(void *pvVjoy);
int func_001449C8(void *pvVjoy);
void UpdateSeqnodeVjoy(void *pseqnode, JOY *pjoy);
void UpdateJtFocus(JT *pjt);
void UpdateJtWater(JT *pjt);
void func_00140750(JT *pjt);
void UpdateJtLookRig(JT *pjt);
int FAsegaGone(void *pasega);
void ReleaseAsegaHandle(void **ppasega);
int FActiveCplcy(void *pcplcy);
int GrfbtnVjoyPressedWithin(JOY *pjoy, int grfbtn, float dt);
void ConsumeJoyButton(JOY *pjoyGlobal, int grfbtn);
void GadgetMenu_Open(void *pgadgetmenu);
void GoalStack_Update(GOALSTACK *pgoalstack);
extern char B_002DE2E0;
extern JOY B_002DFC00;
extern char B_003DA0F0;
}

/* JT slot 16 (Update) */
void UpdateJt(JT *pjt, float dt)
{
    UpdateStep(pjt, dt);
    UpdateJtGadgets(pjt);
    if (FButtonPressedWithin(pjt->pjoy, 0x200, 0.0f))
        func_00140338(pjt);
    if (pjt->zapState == -1) {
        void *pvVjoy = pjt->PvVjoy();
        func_00144640(pvVjoy);
        if (!func_001449C8(pvVjoy)) {
            GOALSTACK *pgoalstack = pjt->pgoalstack();
            int cgoal = pgoalstack->count;
            if (cgoal > 0) {
                pgoalstack->apgoal[cgoal - 1]->FillVjoy(pjt->pjoy);
            } else {
                void *pseqnode = pjt->pseqnode;
                if (pseqnode)
                    UpdateSeqnodeVjoy(pseqnode, pjt->pjoy);
            }
        }
    }
    UpdateJtFocus(pjt);
    UpdateJtWater(pjt);
    func_00140750(pjt);
    UpdateJtLookRig(pjt);
    void *pasega = pjt->pasegaHandle;
    if (pasega && FAsegaGone(pasega))
        ReleaseAsegaHandle(&pjt->pasegaHandle);
    if (!FActiveCplcy(&B_002DE2E0)) {
        JOY *pjoy = pjt->pjoy;
        if (pjoy->field_0x80 == 1 && GrfbtnVjoyPressedWithin(pjoy, 0x100, 0.0f)
            && (B_002DFC00.grfbtnLatest & 0x108) == 0x100) {
            ConsumeJoyButton(&B_002DFC00, 0x100);
            GadgetMenu_Open(&B_003DA0F0);
        }
    }
    if (!func_001449C8(pjt->PvVjoy()))
        GoalStack_Update(pjt->pgoalstack());
}
