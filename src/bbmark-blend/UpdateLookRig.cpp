#include "lookrig.h"
#include "joy.h"
extern "C" {
int FAsegaGone(void *);
int GrfbtnVjoyPressedWithin(float, JOY *, int);
void ClearVjoyPresses(JOY *, int);
void SetLookRigState(LOOKRIG *, int);
}
extern "C" void UpdateLookRig(LOOKRIG *prig, int mode)
{
    if (prig->phandle != 0 && FAsegaGone(prig->phandle) != 0)
        SetLookRigState(prig, -1);
    if (mode != prig->state && prig->state != -1)
        SetLookRigState(prig, mode);
    if (mode != -1 && (prig->state == -1 || prig->field_0xC != 0)) {
        if (GrfbtnVjoyPressedWithin(0.1f, prig->pjt->pjoy, 0x80) != 0 &&
            prig->pjt->FCanUseGadget(2) != 0) {
            ClearVjoyPresses(prig->pjt->pjoy, 0x80);
            SetLookRigState(prig, -1);
            SetLookRigState(prig, mode);
        }
    }
    if ((prig->pjt->pjoy->grfbtn & 0x80) == 0)
        prig->fReleased = 1;
}
