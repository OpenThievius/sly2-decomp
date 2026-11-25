#include "pausemenu.h"
extern "C" void PauseMenu_Push(PAUSEMENU *, int, PAUSEITEM *, PAUSEBLOT *, PAUSELABELS *);
extern PAUSEMENU B_003D9ED0;

void func_001B0688(PAUSEITEM *arg0) {
    PauseMenu_Push(&B_003D9ED0, arg0->citemSub, arg0->aitemSub, 0, arg0->plabelsSub);
    if (arg0 != 0) {
        arg0->grf |= 2;
    }
}
