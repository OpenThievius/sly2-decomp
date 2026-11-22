// SPDX-License-Identifier: GPL-3.0-or-later
#include "keypad.h"
#include "clock.h"

extern "C" {
void StopStream(void *);
void StopJsg(int);
void StartJsg(int, PO *);
int StartStream(void *, int, int);
void SetGadgetAcquired(int, int);
void IncrementSwBinocCount(void *);
void DecrementSwBinocCount(void *);
void IncrementSwShowCount(void *);
void DecrementSwShowCount(void *);
void func_001C8918(void *, int);
extern char B_003DD040;
extern char B_003DD490;
}

void func_001C8730(KEYPAD *self, int state)
{
    if (state == self->state) return;
    if (self->stream != 0) {
        StopStream(&B_003DD040);
        self->stream = 0;
    }
    if (self->jsg != 0) StopJsg(self->jsg);
    switch (self->state) {
    case 2:
        func_001C8918(self, -1);
        DecrementSwShowCount(&B_003DD490);
        break;
    case 3:
        if (self->gadget != -1) SetGadgetAcquired(self->gadget, 1);
        if (self->streamA != 0) self->stream = StartStream(&B_003DD040, self->streamA, 1);
        break;
    case 0:
        if (self->ppoUser != 0) IncrementSwBinocCount(&B_003DD490);
        break;
    }
    self->state = state;
    self->tState = g_2dded0.t;
    switch (state) {
    case -1:
        return;
    case 2:
        self->cnt = 5;
        func_001C8918(self, 1);
        IncrementSwShowCount(&B_003DD490);
        if (self->streamB != 0) self->stream = StartStream(&B_003DD040, self->streamB, 0);
        break;
    case 1:
        self->SetPlayable(1);
        break;
    case 0:
    case 5:
        if (self->ppoUser != 0) {
            self->ppoUser->SetPlayable(1);
            self->ppoUser = 0;
            DecrementSwBinocCount(&B_003DD490);
        }
        break;
    }
    self->jsg = self->ajsg[self->state];
    if (self->jsg != 0) StartJsg(self->jsg, self->ppoUser);
}
