/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

int FIsBasicDerivedFrom(void *, int);
void StartMurrayLift(void *, struct LIFTPT *);
void func_00184130(struct LIFTPT *, void *);

void LiftPt_OnGrab(struct LIFTPT *lift, void *pmurray) {
    func_00184130(lift, pmurray);
    if (FIsBasicDerivedFrom(pmurray, 0x36) != 0) {
        StartMurrayLift(pmurray, lift);
    }
}
