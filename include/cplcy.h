/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The camera policy objects of src/tn-rip/ (C and C++). Every policy starts with the CPLCY header (InitCplcy sets its vtable
   pointer at +0xC; DeactivateCplcy reads +0, +4, +8). The derived classes below are named from the functions that use them:
   CPLOOK (InitCplook), CPCLOSE (bevy_camera_looks_activate's "Close"), K30CAM (bevy_classes_k30_cam_*), CPPOLICY
   (bevy_camera_policy_*: a policy that holds a CPHOLDER, whose object it calls through a vtable entry).
   CM and CPLCY are cm.h's (C++ only): a C++ source gets them from there, a C source gets the C views below (the same offsets; in
   C the policy's vtable pointer is a plain field, in C++ it belongs to the classes that declare virtuals). */
#ifndef SLY2_CPLCY_H
#define SLY2_CPLCY_H
#include "types.h"

#ifdef __cplusplus
#include "cm.h"
#else
/* C view of cm.h's CM */
struct CM {
    u8 unknown_0x0[0x24];
    /* 0x24 */ f32 field_0x24; /* CM::field_0x24 */
};

/* C view of cm.h's CPLCY (0xD0 bytes) */
struct CPLCY {
    u8 unknown_0x0[0xC];
    /* 0xC */ void *vtable; /* InitCplcy sets it; func_00151208, func_00151610, func_001518C8, InitCpman set their own */
    u8 unknown_0x10[0xC0];
};
#endif

struct CPLOOK {
    u8 unknown_0x0[0xC];
    /* 0xC */ void *vtable;
    u8 unknown_0x10[0x10];
    /* 0x20 */ f32 u;  /* UpdateCplook's u */
    /* 0x24 */ f32 du; /* its du */
    /* 0x28 */ f32 field_0x28; /* InitCplook: 7.0 */
    /* 0x2C */ f32 fovMin;
    u8 unknown_0x30[4];
    /* 0x34 */ void *ambience; /* reference pointer (UpdateCplook's pamb); InitCplook and bevy_camera_looks_reset clear it */
    /* 0x38 */ void *field_0x38; /* reference pointer, cleared the same way */
};

struct CPCLOSE {
    u8 unknown_0x0[0xC];
    /* 0xC */ void *vtable;
    u8 unknown_0x10[4];
    /* 0x14 */ s32 lookat; /* func_0012E460 frees it; bevy_camera_looks_activate stores it */
};

struct K30CAM {
    u8 unknown_0x0[0xC];
    /* 0xC */ void *vtable;
    /* 0x10 */ s32 field_0x10; /* bevy_classes_k30_cam_150780 reads it as the target object */
    /* 0x14 */ s32 field_0x14;
    /* 0x18 */ f32 minDistance; /* bevy_classes_k30_cam_150ef0's minDistance */
    u8 unknown_0x1C[0x24];
    /* 0x40 */ s32 active;
    u8 unknown_0x44[0x3C];
    /* 0x80 */ s128 currentPosition; /* bevy_classes_k30_cam_150ef0 */
    /* 0x90 */ s128 currentTarget;
    /* 0xA0 */ f32 currentDistance;
    u8 unknown_0xA4[0x10];
    /* 0xB4 */ f32 field_0xB4; /* func_00150728: 7.0 */
    u8 unknown_0xB8[8];
    /* 0xC0 */ void *field_0xC0; /* reference pointers, cleared by bevy_classes_k30_cam_reset */
    /* 0xC4 */ void *field_0xC4;
};

struct CPVTABLE {
    u8 unknown_0x0[8];
    /* 0x8 */ s16 delta_0x8;
    s16 unknown_0xA;
    /* 0xC */ void (*fn_0xC)(char *);
    /* 0x10 */ s16 delta_0x10;
    s16 unknown_0x12;
    /* 0x14 */ void (*fn_0x14)(char *);
};

struct CPOBJECT {
    u8 unknown_0x0[0xC];
    /* 0xC */ struct CPVTABLE *vtable;
};

struct CPHOLDER {
    u8 unknown_0x0[0x14];
    /* 0x14 */ struct CPOBJECT *object;
};

struct CPSOURCE {
    u8 unknown_0x0[0xC];
    /* 0xC */ s32 field_0xC; /* bevy_camera_policy_deactivate tests it */
};

struct CPPOLICY {
    u8 unknown_0x0[0x10];
    /* 0x10 */ struct CPHOLDER *holder;
};

struct CPATTACHSOURCE {
    u8 unknown_0x0[0x1BC];
    /* 0x1BC */ f32 field_0x1BC; /* ActivateCpattach copies it into the camera manager */
};

#endif
