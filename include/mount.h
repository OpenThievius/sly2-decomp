/* SPDX-License-Identifier: GPL-3.0-or-later */
/* MOUNT, a SOHIT (sohit.h) that carries part records (Mount_Init, Mount_PostLoad, Mount_OnPoActive, Mount_BindRecords: the Mount_ names
   of config/recovered/decomp_names.md). Its size is not known; only the record list is declared. C++ only. */
#ifndef SLY2_MOUNT_H
#define SLY2_MOUNT_H
#include "sohit.h"

/* a part record, 0x18 bytes: an xf part and an SM object, found by oid (Mount_BindRecords), with what binding them gave */
struct MOUNTREC { s32 oidPart; s32 oidObject; void *pxf; void *pact; void *plo; void *psma; };

struct MOUNT : SOHIT {
    u8 unknown_0x1A0[0x90]; /* SOHIT is 8-aligned: its size is 0x1A0 */
    /* 0x230 */ s32 crec;         /* Mount_BindRecords (func_0017F770), Mount_AddPart (0x1800A0, named UseStepguardDeathAnimation by a wrong match): count, at most 4 */
    /* 0x234 */ MOUNTREC arec[1]; /* the same two: the records (room for four) */
};
#endif
