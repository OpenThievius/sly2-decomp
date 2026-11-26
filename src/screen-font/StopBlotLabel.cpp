#include "blot.h"
#include "sly2.h"
extern "C" void StopRootSprite(void*);
extern "C" void SetBlotModal(BLOT*, int);
extern "C" void StopBlotLabel(BLOT* pblot)
{
    StopRootSprite((void *)pblot->asprite);
    if (pblot->modal != 0)
        SetBlotModal(pblot, -1);
    pblot->Slot21(0);
    pblot->HandleSpliceEvent(6, 0, 0, 0, 0);
    pblot->labelTime = 0;
    pblot->cur = -1;
}
