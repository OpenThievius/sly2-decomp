// SPDX-License-Identifier: GPL-3.0-or-later
#include "dprize.h"

/* the channel object PchnFindAseg finds for the animation: its slot 3 fills the three scales */
struct CHN {
    virtual void Slot1();
    virtual void Slot2();
    virtual void GetScale(float *pgScale, int, float t, float u); /* 3: RenderDprizeAll passes a result buffer, 0 and the animation's two values */
};
struct CHNENTRY {
    u8 unknown_0x0[0x4];
    /* 0x4 */ CHN *pchn;
};
/* the animation handle's two values the scale is asked for (asega.h declares tLocal, 0x1C): only this function reads 0x40 */
struct ASEGAVIEW : ASEGA {
    u8 unknown_0x20[0x20];
    /* 0x40 */ f32 field_0x40;
};
/* retail's 0x90-byte frame buffer (the layout and copy of the matched RenderLoot): the scales at 0, a copy of the matrix at 0x10,
   the matrix built from them at 0x50 */
struct RENDERFRAME {
    float scale[4];
    MATRIX4 matCopy;
    MATRIX4 matBuilt;
};
extern "C" void func_001F3C70(DPRIZE *);
extern "C" void func_001A5EE8(DPRIZE *, MATRIX4 *, float, float);
extern "C" void LoadMatrixFromPosRotScale(MATRIX4 *, QW, MATRIX3 *, float *);
extern "C" CHNENTRY *PchnFindAseg(ASEG *, DPRIZE *, int, int);
extern "C" QW PosLoWorld(DPRIZE *);
extern "C" MATRIX3 *PmatLoWorld(DPRIZE *);
// Retail's virtual call through the channel passes a0 (object adjusted by the vtable delta at +0x18), a1 = the scale buffer,
// a2 = 0, f12 and f13 only: $a3 merely holds the object pseudo (a free argument register), as in SnapAsega, so the method takes
// (float *, int, float, float) and no fourth integer argument.
extern "C" void RenderDprizeAll(DPRIZE *pdprize)
{
    RENDERFRAME frame;
    if (pdprize->dprizes != 2) {
        SMA *psma = pdprize->psma;
        ASEGAVIEW *pasega;
        if (psma != 0 && (pasega = (ASEGAVIEW *)psma->pasega) != 0) {
            CHNENTRY *pentry = PchnFindAseg(pasega->paseg, pdprize, 0xC, 1);
            if (pentry != 0) {
                pentry->pchn->GetScale(frame.scale, 0, pasega->tLocal, pasega->field_0x40);
                MATRIX4 *pmat = &frame.matBuilt;
                QW pos = PosLoWorld(pdprize);
                LoadMatrixFromPosRotScale(pmat, pos, PmatLoWorld(pdprize), frame.scale);
                frame.matCopy = frame.matBuilt;
                func_001A5EE8(pdprize, &frame.matCopy, pdprize->uFade, pdprize->uFade);
            } else {
                func_001F3C70(pdprize);
            }
        } else {
            func_001F3C70(pdprize);
        }
    }
}
