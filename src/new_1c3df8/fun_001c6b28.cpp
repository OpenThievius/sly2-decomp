// SPDX-License-Identifier: GPL-3.0-or-later
#include "dprize.h"

extern "C" {
void *NewEmitter(int);
void SetEmitterUnpositioned(void *, int);
void RequestTaskState(void *, int, void *);
void SetDprizeDprizes(DPRIZE *, int);
}

// SetDprizeKeyDprizes: state 1 asks the task for state 2
void func_001C6B28(DPRIZEKEY *pkey, int dprizes)
{
    if (pkey->dprizes != dprizes) {
        if (dprizes == 1) {
            void *pemitter = NewEmitter(0);
            SetEmitterUnpositioned(pemitter, 0);
            if (pkey->ptask)
                RequestTaskState(pkey->ptask, 2, pkey);
            dprizes = 2;
            pkey->HandleSpliceEvent(5, 0, 0, 0, 0);
        }
        SetDprizeDprizes(pkey, dprizes);
    }
}
