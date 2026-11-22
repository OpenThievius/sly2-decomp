// SPDX-License-Identifier: GPL-3.0-or-later
// 0x258438 CTextBox::SetPos
#include "ctextbox.h"
extern "C" void CTextBox_SetPos(CTextBox *ptextbox, float x, float y)
{
    ptextbox->x = x;
    ptextbox->y = y;
}
