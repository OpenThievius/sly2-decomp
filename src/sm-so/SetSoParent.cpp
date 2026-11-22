// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "xf.h"
#include "so.h"
extern "C" {
void SetLoParent(SO *, SO *, int, int);
void UpdateAloXfWorld(SO *);
void __ml__FRC7MATRIX4T0(MATRIX4 *, void *, MATRIX4 *);
void func_001F2468(SO *);
void func_001F26A8(SO *);
void func_001F8668(SO *, int);
void SetSoParent(SO *self, SO *newParent, int arg2, int arg3)
{
    MATRIX4 mat;
    QW pos;
    QW vel;
    QW pos2;
    if (arg3 & 3) {
        if ((int)(self->grfo >> 60) & 1) {
            mat = *(MATRIX4 *)((char *)self->pxfRoot + 0x40);
        } else {
            memset(&mat, 0, 0x40);
            XF *node = self->pxfRoot;
            mat.mat[3][3] = 1.0f; //P
            mat.mat[2][2] = 1.0f; //P
            mat.mat[1][1] = 1.0f; //P
            mat.mat[0][0] = 1.0f; //P
            if (node != 0) {
                do {
                    MATRIX4 product;
                    __ml__FRC7MATRIX4T0(&product, &node->mat, &mat);
                    mat = product;
                    node = node->pxfParent;
                } while (node != 0);
            }
        }
    }
    int flag4 = arg3 & 4;
    if (flag4 != 0) {
        pos = self->GetVelocityVec();
    }
    int flag8 = arg3 & 8;
    if (flag8 != 0) {
        vel = self->Slot34();
    }
    SO *owner = self->psoParent;
    int rangeCount;
    int rangeBase;
    if (owner != 0) {
        rangeCount = owner->cxf;
        rangeBase = (int)owner->axf;
    } else {
        rangeCount = 1;
        rangeBase = 0;
    }
    int value;
    if (arg2 != 0)
        value = arg2;
    else if (newParent != 0)
        value = (int)newParent->pxfRoot;
    else
        value = 0;
    int index = 0;
    if (self->cxf > 0) {
        do {
            int *slot = (int *)&self->axf[index].pxfParent;
            int rel = (*slot - rangeBase) >> 8;
            if (rel >= 0 && rel < rangeCount)
                *slot = value;
            index++;
        } while (index < self->cxf);
    }
    SetLoParent(self, newParent, arg2, arg3);
    UpdateAloXfWorld(self);
    if (arg3 & 1) {
        self->TranslateToPos(*(QW *)&mat.mat[3][0]);
    }
    if (arg3 & 2) {
        self->Slot30(&mat);
    }
    if (flag4 != 0) {
        self->Slot35(pos);
    }
    if (flag8 != 0) {
        self->Slot36(vel);
    }
    func_001F2468(self);
    func_001F26A8(self);
    SO *owner2 = self->psoParent;
    if (owner2 != 0 && !(owner2->grfso & (0x8000UL << 20)))
        func_001F8668(self, 0);
}
}
