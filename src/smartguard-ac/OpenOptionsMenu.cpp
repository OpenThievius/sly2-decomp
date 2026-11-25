/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
#include "pausemenu.h"
extern "C" {
extern PAUSEITEM D_002BFEC8[];
extern PAUSEITEM B_002F6470[];
extern PAUSEMENU B_003D9ED0;
extern char B_003DA530;
extern PAUSELABELS D_002BFD38;
int CGc_FFindScreen(void *);
void PauseMenu_Push(PAUSEMENU *, int, PAUSEITEM *, PAUSEBLOT *, PAUSELABELS *);
void func_001AF390(PAUSEMENU *, int, PAUSEITEM *);
}
void OpenOptionsMenu(PAUSEITEM *caller)
{
    PAUSEITEM *source = D_002BFEC8;
    PAUSEITEM *dest = B_002F6470;
    unsigned index = 0;
    do {
        int show = 1;
        switch (source->kind) {
        case 0x3D:
            break;
        case 0x3C:
            show = CGc_FFindScreen(&B_003DA530) != 0;
            break;
        case 0x3E:
            show = CGc_FFindScreen(&B_003DA530) == 0;
            break;
        }
        if (show) {
            *dest = *source;
            dest++;
        }
        index++;
        source++;
    } while (index < 11);
    if (caller) {
        func_001AF390(&B_003D9ED0, dest - B_002F6470, B_002F6470);
        caller->grf |= 2;
    } else {
        PauseMenu_Push(&B_003D9ED0, dest - B_002F6470, B_002F6470, B_003D9ED0.pblot, &D_002BFD38);
    }
}
