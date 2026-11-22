// SPDX-License-Identifier: GPL-3.0-or-later
#include "ctextbox.h"
extern "C" void CTextBox_SetSize(CTextBox *ptextbox, float dx, float dy)
{
    ptextbox->dx = dx;
    ptextbox->dy = dy;
}
