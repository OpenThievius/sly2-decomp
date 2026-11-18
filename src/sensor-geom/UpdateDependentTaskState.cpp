#include "sly2.h"
struct TASK { char pad0[0x54]; int nState; char pad58[0x3C]; int cPrereq; TASK **apPrereq; char pad9C[0x54]; int nPending; };
static inline int GetCount(TASK *task) { return task->cPrereq; }
static inline int GetState(TASK *task) { return task->nState; }
extern "C" void SetTaskStateCascade(TASK *, int);
extern "C" void UpdateDependentTaskState(TASK *ptask, int nStateParent)
{
    if (ptask->nPending != -1)
        return;
    int nStateOld = GetState(ptask);
    int nState = nStateOld;
    if (nStateParent >= 0) {
        if (nStateParent < 2) {
            nState = 0;
        } else if (nStateParent < 4) {
            int fAllComplete = 1;
            for (int itask = 0; itask < ptask->cPrereq; itask++) {
                if (ptask->apPrereq[itask]->nState < 2) {
                    fAllComplete = 0;
                    break;
                }
            }
            if (!fAllComplete)
                nState = 0;
            else switch (nStateOld) {
            case 0: nState = 1; break;
            case 1: case 2: break;
            case 3: nState = nStateParent; break;
            }
        }
    }
    SetTaskStateCascade(ptask, nState);
}
