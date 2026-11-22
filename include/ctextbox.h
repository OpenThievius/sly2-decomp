/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CTextBox, a text box: its position and size, its colour and the two justifications (the setters CTextBox_SetPos, SetSize,
   SetTextColor, SetHorizontalJust, SetVerticalJust each write one part; CTextBox_15FFD0 in font/PglyffFromCh_file.cpp and the
   CTextBox of DrawMpegFrame and GadgetMenu_DrawSlotLabels use the same layout; SetupDraw clips to x, y, dx and dy). C and C++. */
#ifndef SLY2_CTEXTBOX_H
#define SLY2_CTEXTBOX_H
#include "types.h"

typedef struct CTextBox {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 dx;       /* SetupDraw clips to x + dx * 512 */
    /* 0x0C */ f32 dy;
    /* 0x10 */ u8 rgba[4];   /* CTextBox_SetTextColor copies a colour word (unaligned) */
    /* 0x14 */ s32 justH;    /* CTextBox_SetHorizontalJust */
    /* 0x18 */ s32 justV;    /* CTextBox_SetVerticalJust */
} CTextBox;

#endif
