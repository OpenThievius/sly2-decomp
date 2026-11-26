#include "rtalo.h"
#include "sw.h"
#include "sly2.h"
extern "C" {
extern ROGWINDOW B_003E1A78[];
extern char B_003DD4BC[];
int FIsLoInWorld(void *);
void AppendDlEntry(void *, void *);
}
ROGWINDOW *func_001BEB28(RTALO *alo)
{
    if (alo->pwindow == 0) {
        for (unsigned slotIndex = 0; slotIndex < 2; slotIndex++) {
            ROGWINDOW *candidate = &B_003E1A78[slotIndex];
            if (candidate->pcamobj == 0) {
                alo->pwindow = candidate;
                break;
            }
        }
        if (alo->pwindow != 0) {
            alo->pwindow->pcamobj = alo;
            for (int index = 0; index < alo->count; index++) {
                u32 *pflag = &alo->aflag[index];
                SO *child = alo->apso[index];
                *pflag = 0;
                if (((child->grfo >> 60) & 1) == 0) {
                    *pflag = 1;
                    child->Add();
                    if (FIsLoInWorld(child) == 0) {
                        AppendDlEntry(B_003DD4BC, (void *)child->proot);
                        LO *inner = *(LO **)child->proot;
                        inner->Slot23();
                    }
                }
                u32 flags = child->grfSw;
                if (((flags ^ 1) & 1) != 0)
                    flags = child->pgrfentry->grf;
                if ((flags & 8) != 0) {
                    *pflag |= 2;
                    child->Slot21(0);
                }
            }
            alo->Slot21(1);
            alo->HandleSpliceEvent(2, 0, 0, 0, 0);
        }
    }
    return alo->pwindow;
}
