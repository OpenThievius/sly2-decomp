#include "jobmenu.h"
#include "blot.h"
extern "C" {
void SwitchBlotLabel(BLOT *, int, void *);
int FEndTaskComplete(JOB *);
int FTaskComplete(TASK *);
}

void JobMenu_UpdateBlot(JOBMENU *pjobmenu)
{
    if (pjobmenu->pblot->blots != 2)
        return;
    for (int irow = 0; irow < pjobmenu->cent; irow++) {
        JOBROW *prow = &pjobmenu->aent[irow];
        int labelRow = (irow == pjobmenu->isel) ? 0x4FD + irow : 0x4E9 + irow;
        SwitchBlotLabel(pjobmenu->pblot, labelRow, &prow->label);
        int fComplete = 0;
        switch (pjobmenu->page) {
        case 0:
            fComplete = FEndTaskComplete(prow->pjob);
            break;
        case 1:
            fComplete = FTaskComplete(prow->ptask);
            break;
        }
        SwitchBlotLabel(pjobmenu->pblot, fComplete != 0 ? 0x507 + irow : -1, &prow->labelDone);
    }
}
