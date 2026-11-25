#include "sly2.h"
#include "hitfx.h"
struct REFH {
    HITFX *p;
    REFH(HITFX *target) { p = target; }
    ~REFH() { p->Slot2(); }
};
extern "C" int FHitFxGone(HITFX *);
extern "C" void RemoveDlEntry(void *, HITFX *);
extern char B_003E148C;
extern "C" void HitFx_Remove(HITFX *pfx)
{
    if (FHitFxGone(pfx) == 0) {
        REFH ref(pfx);
        pfx->OnAdd();
        pfx->PostMessage(0xF, pfx);
        if (FHitFxGone(pfx) != 0) {
            return;
        }
        {
            RemoveDlEntry(&B_003E148C, pfx);
            pfx->HandleSpliceEvent(3, 0, 0, 0, 0);
            pfx->Slot2();
        }
    }
}
