#include "rtalo.h"
#include "sly2.h"
void func_001BED18(RTALO *alo)
{
    ROGWINDOW *slot = alo->pwindow;
    if (slot) {
        slot->pcamobj = 0;
        alo->pwindow = 0;
        for (int index = 0; index < alo->count; index++) {
            SO *child = alo->apso[index];
            if (alo->aflag[index] & 1)
                child->Remove();
            if (alo->aflag[index] & 2)
                child->Slot21(1);
        }
        alo->Slot21(0);
        alo->HandleSpliceEvent(3, 0, 0, 0, 0);
    }
}
