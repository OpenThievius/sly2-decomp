#include "sly2.h"
/* the menu object (Menu_Update, ShopMenu_*): 0x30 the dialog kind (-1 none, 0 or the general one), 0x34 the time it ends, 0x38 its argument */
struct MENU {
    u8 unknown_0x0[0x30];
    /* 0x30 */ s32 dialogKind;
    /* 0x34 */ f32 tDialogEnd;
    /* 0x38 */ s32 dialogArg;
};
extern "C" float g_2ddf0c;
extern "C" float D_002C3254;
extern "C" void *NewEmitter(int);
extern "C" void SetEmitterUnpositioned(void *, int);
extern "C" void Menu_SetDialog(MENU *self, int kind, int arg)
{
    self->dialogArg = arg;
    self->dialogKind = kind;
    if (kind == 0) goto zero;
    if (kind > 0) goto general;
    if (kind != -1) goto general;
    self->tDialogEnd = -10.0f;
    return;
zero:
    self->tDialogEnd = 3.402823466e+38f;
    SetEmitterUnpositioned(NewEmitter(0x29), 0);
    return;
general:
    self->tDialogEnd = g_2ddf0c + D_002C3254;
    SetEmitterUnpositioned(NewEmitter(0x36), 0);
}
