#include "sw.h"
/* What Sw_Construct writes outside SW's declared fields: the vtable pointer it sets by hand (as a compiler-made constructor
   would) and the 0x200 lists from 0x38, which overlap SW::state (0x150) as sw.h has it. */
struct SWCTORVIEW {
    u8 unknown_0x0[0xC];
    void *vtable;
    u8 unknown_0x10[0x28];
    SL asl[0x200];
};
extern "C" {
void *CreateSlotheapSwAlign(SLOTHEAP *, int, int, int);
void InitDl__FP2DLi(void *, int);
void InitSl(void *, int);
int func_001CF5C8();
void *memset(void *, int, unsigned);
extern char D_002DC018[];
extern float D_002C3E60, D_002C3E64, D_002C3E68, D_002C3E6C;
SW *Sw_Construct(SW *this_)
{
    this_->pframe = 0;
    this_->psidebag = 0;
    ((SWCTORVIEW *)this_)->vtable = D_002DC018;
    CreateSlotheapSwAlign(&this_->field_0x398C, 0x14, 0x100, 0x10);
    CreateSlotheapSwAlign(&this_->slotheapTimedcall, 0x14, 0x100, 0x10);
    CreateSlotheapSwAlign(&this_->slotheapCb, 0x14, 0x100, 0x10);
    CreateSlotheapSwAlign(&this_->field_0x3CB4, 0xC, 0x200, 0x10);
    CreateSlotheapSwAlign(&this_->slotheapOxa, 0x80, 0x300, 0x10);
    CreateSlotheapSwAlign(&this_->slotheapOx, 0x14, 0x400, 0x10);
    CreateSlotheapSwAlign(&this_->slotheapMq, 0xC0, 0x100, 0x10);
    CreateSlotheapSwAlign(&this_->field_0x3D94, 0x60, 0x100, 0x10);
    CreateSlotheapSwAlign(&this_->field_0x3DAC, 0x80, 0x400, 0x10);
    CreateSlotheapSwAlign(&this_->field_0x3DC4, 0x14, 8, 0x10);
    CreateSlotheapSwAlign(&this_->field_0x3DE8, 0x50, 0x80, 0x10);
    this_->field_0x3E00 = 0x80000000;
    CreateSlotheapSwAlign(&this_->field_0x3E44, 0x30, 0x40, 0x10);
    CreateSlotheapSwAlign(&this_->slotheapHitfx, 0x60, 0x40, 0x10);
    CreateSlotheapSwAlign(&this_->slotheapRipg, 0x1B0, 0x10, 0x10);
    int cb = func_001CF5C8();
    CreateSlotheapSwAlign(&this_->slotheapRip, (cb != 0) ? cb : 0xF0, 0x80, 0x10);
    CreateSlotheapSwAlign(&this_->slotheapBlipg, 0x460, 0x28, 0x10);
    CreateSlotheapSwAlign(&this_->slotheapBlip, 0x10C0, 0x80, 0x40);
    CreateSlotheapSwAlign(&this_->slotheapBlipSp, 0x560, 8, 0x10);
    CreateSlotheapSwAlign(&this_->field_0x40B8, 0x1C, 0x200, 0x10);
    CreateSlotheapSwAlign(&this_->field_0x40D0, 0xF0, 0x20, 0x10);
    CreateSlotheapSwAlign(&this_->slotheapXa, 0x10, 0x10, 0x10);
    CreateSlotheapSwAlign(&this_->slotheapWkr, 0x60, 0x20, 0x10);
    CreateSlotheapSwAlign(&this_->field_0x413C, 0x30, 0x10, 0x10);
    CreateSlotheapSwAlign(&this_->field_0x4648, 0x40, 0x10, 0x10);
    CreateSlotheapSwAlign(&this_->field_0x4660, 0xD0, 0x10, 0x10);
    InitDl__FP2DLi(&this_->field_0x10, 0x24);
    InitDl__FP2DLi(&this_->dlRoot, 4);
    InitDl__FP2DLi(&this_->dlRootNext, 0xC);
    InitDl__FP2DLi(&this_->dlOxa, 0x48);
    InitDl__FP2DLi(&this_->pnodeFirst, 0x40);
    InitDl__FP2DLi(&this_->dlOxaRecalc, 0x50);
    InitDl__FP2DLi(&this_->dlOxaDirty, 0x58);
    InitDl__FP2DLi(&this_->dlAsega, 0x24);
    InitSl(&this_->ptimedcallFirst, 0x10);
    InitSl(&this_->pcbFirst, 0x10);
    InitDl__FP2DLi(&this_->field_0x3F24, 0xE0);
    InitDl__FP2DLi(&this_->field_0x3F30, 0x1B4);
    InitDl__FP2DLi(&this_->field_0x3F3C, 0x1B4);
    InitDl__FP2DLi(&this_->field_0x3F48, 0x104);
    InitDl__FP2DLi(&this_->field_0x3F54, 0x174);
    InitDl__FP2DLi(&this_->field_0x3F60, 0x1B4);
    InitDl__FP2DLi(&this_->field_0x3F6C, 0x104);
    InitDl__FP2DLi(&this_->field_0x3F78, 0x104);
    InitDl__FP2DLi(&this_->field_0x3F84, 0x104);
    InitDl__FP2DLi(&this_->field_0x3F90, 0xE0);
    InitDl__FP2DLi(&this_->field_0x3FA8, 0x154);
    InitDl__FP2DLi(&this_->field_0x3F9C, 0x100);
    InitDl__FP2DLi(&this_->field_0x3DDC, 0x1C);
    InitDl__FP2DLi(&this_->dlHitfx, 0x58);
    InitDl__FP2DLi(&this_->field_0x3FB4, 0xFE0);
    InitDl__FP2DLi(&this_->field_0x3FC0, 0x174);
    InitSl(&this_->pvjoyFirst, 0x84);
    InitSl(&this_->field_0x4100, 0x18);
    InitSl(&this_->field_0x410C, 0x40);
    InitDl__FP2DLi(&this_->dlWkr, 0x50);
    InitDl__FP2DLi(&this_->field_0x3FCC, 0x20);
    InitDl__FP2DLi(&this_->field_0x3FD8, 0x104);
    InitDl__FP2DLi(&this_->field_0x45B0, 0x1D0);
    InitDl__FP2DLi(&this_->field_0x45BC, 0x1E0);
    InitDl__FP2DLi(&this_->field_0x3B00, 0x88);
    InitDl__FP2DLi(&this_->field_0x3FE4, 0xE0);
    InitDl__FP2DLi(&this_->field_0x3FF0, 0x130);
    InitDl__FP2DLi(&this_->field_0x3BD0, 0xB4);
    InitSl(&this_->field_0x3BDC, 0x4C);
    for (u32 i = 0; i < 0x200; i++)
        InitSl(&((SWCTORVIEW *)this_)->asl[i], 0x1C);
    f32 *phsv = (f32 *)&this_->hsvFog;
    f32 *pv2 = this_->field_0x45E0;
    f32 *pv3 = this_->field_0x45D0;
    u32 *pgrf = this_->grfLightSlotFree;
    SL *psl = this_->aslCid;
    for (s32 i = 0xC6; i >= 0; i--) {
        InitSl(psl, 0x20);
        psl++;
    }
    for (u32 i = 0; i < 0x200; i++)
        InitSl(&this_->field_0x1838[i], 0xC);
    float fd = D_002C3E6C, fc = D_002C3E68, fb = D_002C3E64, fa = D_002C3E60;
    float denom = fb - fa;
    ((f32 *)&this_->hsvFog)[0] = 180.0f;
    phsv[1] = 255.0f;
    phsv[2] = 255.0f;
    this_->scaleFog = 90.0f;
    this_->field_0x3E64 = 128.0f;
    this_->field_0x3E68 = 96.0f;
    this_->field_0x3E6C = 160.0f;
    this_->field_0x3C88 = 0x189;
    this_->field_0x3C80 = -1;
    this_->field_0x3C8C = -1;
    this_->fAaoxDirty = 1;
    this_->field_0x45E0[0] = fd;
    this_->field_0x3F10 = -2;
    this_->alphaFog = 0;
    pv2[1] = fc;
    this_->field_0x45D0[0] = (fb * fc - fa * fd) / denom;
    pv3[1] = (fd - fc) / denom;
    pv3[2] = 0;
    this_->field_0x4740 = -1;
    this_->field_0x4750 = -60.0f;
    this_->tL3 = -60.0f;
    this_->fLightsDirty = 1;
    memset(pgrf, -1, 0x20);
    return this_;
}
}
