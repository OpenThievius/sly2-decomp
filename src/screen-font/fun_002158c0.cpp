#include "fbsprite.h"
#include "sly2.h"
extern "C" void StopSpriteInstance(SPRITE*, int);
extern "C" void func_001BED18(void*);
extern "C" void InitDepthSlot(SLOT*);
extern "C" void func_002158C0(MOVIECHAR* pchar, SLOT* pslot)
{
    switch (pchar->type) {
    case 4:
        StopSpriteInstance(&((SPRITE *)pchar->pblot->asprite)[pchar->id], pslot->iinst);
        break;
    case 6:
        if (pchar->pwindow != 0) {
            void* held = pchar->pwindow->pcamobj;
            if (held != 0)
                func_001BED18(held);
            pchar->pwindow = 0;
        }
        break;
    }
    InitDepthSlot(pslot);
}
