// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
#include "jt.h"
#include "pausemenu.h"
/* an unmapped object: OpenPauseMenu tests the word at 0x24 */
struct G1 { u8 unknown_0x0[0x24]; s32 f; };
extern "C" {
extern PAUSEITEM D_002C00E8[];
extern PAUSEITEM B_002F65D0[];
extern PAUSEMENU B_003D9ED0;
extern SW B_003DD490;
extern G1 B_003DA3C0;
extern char B_002E6550[];
extern PAUSELABELS D_002BFD38;
int FSwLoadBusy(SW *);
int CGc_FFindScreen(void *);
void *PpoSwFocusBase(SW *);
int FIsBasicDerivedFrom(void *, int);
void SetBinocState(void *, int);
int func_002127C8();
int IEpisodeCurrent();
int CidGetBasic(void *);
void PauseMenu_Push(PAUSEMENU *, int, PAUSEITEM *, PAUSEBLOT *, PAUSELABELS *);
}
int OpenPauseMenu(PAUSEITEM *pitemCaller)
{
    if (B_003D9ED0.pblot == 0) return 0;
    if (FSwLoadBusy(&B_003DD490) != 0) return 0;
    if (CGc_FFindScreen(B_002E6550) != 0) return 0;
    void *ppo = PpoSwFocusBase(&B_003DD490);
    if (ppo != 0) {
        if (FIsBasicDerivedFrom(ppo, 0x34) != 0)
            SetBinocState(((JT *)ppo)->unknown_0xF00, -1);
    }
    if (func_002127C8() == 0) return 0;
    {
    PAUSEITEM *source = D_002C00E8;
    PAUSEITEM *dest = B_002F65D0;
    unsigned index = 0;
    do {
        int show = 1;
        switch (source->kind) {
        case 0x2C:
            break;
        case 0x6A:
            show = 0;
            if (B_003DA3C0.f != 0)
                if (IEpisodeCurrent() != 0) show = 1;
            break;
        case 0x6B:
            show = 0;
            if (B_003DD490.pjobCurrent != 0)
                if (IEpisodeCurrent() != 0) show = 1;
            break;
        case 0x43:
            show = 0;
            if (ppo != 0) {
                int cid = CidGetBasic(ppo);
                if (cid < 0x38) {
                    if (cid >= 0x35) show = 1;
                }
            }
            break;
        case 0x42:
            show = IEpisodeCurrent() != 0;
            break;
        }
        if (show) {
            *dest = *source;
            dest++;
        }
        index++;
        source++;
    } while (index < 7);
    PauseMenu_Push(&B_003D9ED0, dest - B_002F65D0, B_002F65D0, B_003D9ED0.pblot, &D_002BFD38);
    if (pitemCaller != 0)
        pitemCaller->grf |= 2;
    return 1;
    }
}
