/* SPDX-License-Identifier: GPL-3.0-or-later */
/* MOUNT, a SOHIT (sohit.h) that carries part records (Mount_Init, Mount_PostLoad, Mount_OnPoActive, Mount_BindRecords: the Mount_ names
   of config/recovered/decomp_names.md). Its size is not known; only the fields read so far are declared. Compiles as C and C++: in C
   (the C sources of this module) SOHIT does not exist and the same fields follow 0x1C0 bytes of unknown. */
#ifndef SLY2_MOUNT_H
#define SLY2_MOUNT_H
#include "types.h"
#ifdef __cplusplus
#include "sohit.h"
#endif
#include "pzo_hide.h" /* ANIMENTRY; after the guard above, so pzo_hide.h's own include of mount.h finds it done */

/* a part record, 0x18 bytes: an xf part and an SM object, found by oid (Mount_BindRecords), with what binding them gave */
struct MOUNTREC { s32 oidPart; s32 oidObject; void *pxf; void *pact; void *plo; void *psma; };

#define MOUNT_FIELDS \
    /* 0x1C0 */ s32 state;               /* Mount_Init sets -1; Mount_SetState (and Chaser, Grab for their own: the slot is shared) */ \
    /* 0x1C4 */ f32 tState;              /* the clock at the last state change (Mount_SetState) */ \
    /* 0x1C8 */ struct ANIMENTRY aentry[5]; /* Mount_Init clears them (func_0017F3E0), Mount_PostLoad resolves them (func_0017F408), Mount_SetState plays the one of the new state (func_0017F4C0) */ \
    u8 unknown_0x218[0x18]; \
    /* 0x230 */ s32 crec;                /* Mount_BindRecords (func_0017F770), Mount_AddPart (0x1800A0, named UseStepguardDeathAnimation by a wrong match): count, at most 4 */ \
    /* 0x234 */ struct MOUNTREC arec[4]; /* the same two: the records */ \
    u8 unknown_0x294[0x14]; \
    /* 0x2A8 */ s32 field_0x2A8;         /* Mount_Init (a method) sets -1 */

#ifdef __cplusplus
struct MOUNT : SOHIT {
    MOUNT_FIELDS
};
#else
struct MOUNT {
    u8 unknown_0x0[0x1C0];
    MOUNT_FIELDS
};
#endif
#endif
