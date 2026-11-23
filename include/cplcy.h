/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CPLCY, the base of the camera manager's policies, and the policy classes (C and C++).

   CPLCY: 0x10 bytes, three words and the vtable pointer at 0xC (g++ 2.95 puts it after the first virtual class's own fields, as
   lo.h explains). Every policy vtable (D_002CD570 for the base, InitCplcy) has seven slots after the type-info entry, declared
   here in slot order; a signature is written only where a matched caller shows it (RevokeCmPolicy, UpdateCmLast,
   bevy_camera_cm_14d650), the others are `void ()` placeholders.

   The policy classes are named from the functions that use them: CPTN (InitCptn, the tunnel), CPLOOK (InitCplook), CPLCYCAMOBJ
   (InitCplcyCamobj), CPCLOSE (bevy_camera_looks_activate's "Close"), CPPOLICY (bevy_camera_policy_*: a policy that holds a
   CPHOLDER, whose object it calls through a vtable entry), K30CAM (bevy_classes_k30_cam_*), CPLOOKAT (ActivateCplookat). Each one's
   size is the distance between its member and the next in the camera manager (cm.h's CM, which CM_Construct and InitCm build at
   those offsets). The field rule is lo.h's: a field read by one of the class's own functions (its init function or a function
   of its vtable) is enough.

   In C++ each policy class derives from CPLCY (its own fields start at 0x10, after the base's vtable pointer) and cm.h's CM holds
   them as members. In C, CPLCY is a plain struct whose vtable pointer is a field, and each policy class starts with the base's
   words as CPLCY_C_HEADER: the C sources set `vtable` themselves after InitCplcy (CPLCY_BASE and CPLCY_C_HEADER give the one
   field list both languages). The C view of CM at the end has only what the C sources read. */
#ifndef SLY2_CPLCY_H
#define SLY2_CPLCY_H
#include "types.h"

#ifdef __cplusplus
struct SO;
struct JOY;
struct CPDEFI;

struct CPLCY {
    /* 0x0 */ s32 active;              /* DeactivateCplcy clears it (ActivateCplcy stores its argument) */
    /* 0x4 */ f32 savedRadFovTarget;   /* ActivateCplcy saves CM::radFovTarget, DeactivateCplcy puts it back; func_0014F5F8 sets it
                                          on the current policy */
    /* 0x8 */ f32 savedNearClip;       /* ActivateCplcy saves CM::sNearClip, DeactivateCplcy hands it to SetCmNearClip;
                                          bevy_camera_cm_14f630 sets it on the current policy */
    /* 0xC: the vtable pointer */
    virtual void Destruct();                      /* 1: CPLCY_Destruct */
    virtual void Activate(SO *pso, void *pv);     /* 2: ActivateCplcy; RevokeCmPolicy passes the new first record's object and data */
    virtual void Deactivate(SO *pso, void *pv);   /* 3: DeactivateCplcy; RevokeCmPolicy passes the old first record's */
    virtual void Set();                           /* 4: SetCplcy */
    virtual void Revoke(void *pv);                /* 5: RevokeCplcy; RevokeCmPolicy passes each revoked record's data */
    virtual void Update(CPDEFI *pcpdefi, JOY *pjoy); /* 6: UpdateCplcy; UpdateCmLast passes the focus's CPDEFI (or 0) and a
                                                     controller: B_002DFC00 or B_002E0D00 by g_2dfbc0 (both JOYs, joy.h) */
    virtual void Reset();                         /* 7: ResetCplcy; bevy_camera_cm_14d650 calls it on every record */
};
#define CPLCY_BASE : CPLCY
#define CPLCY_C_HEADER
#else
/* C view of CPLCY: the vtable pointer is a plain field */
struct CPLCY {
    /* 0x0 */ s32 active; /* DeactivateCplcy clears it (ActivateCplcy stores its argument) */
    /* 0x4 */ f32 savedRadFovTarget; /* DeactivateCplcy copies it back to CM::radFovTarget (ActivateCplcy saves it) */
    /* 0x8 */ f32 savedNearClip; /* DeactivateCplcy hands it to SetCmNearClip (ActivateCplcy saves the camera manager's) */
    /* 0xC */ void *vtable; /* InitCplcy sets it; func_00151208, func_00151610, func_001518C8, InitCpman, CM_Construct set their own */
};
#define CPLCY_BASE
#define CPLCY_C_HEADER u8 unknown_0x0[0xC]; /* CPLCY's words */ void *vtable; /* 0xC: CPLCY's vtable pointer */
#endif

/* CPTN, the tunnel's camera policy, 0xA0 bytes: InitCptn (the vtable), DeactivateCptn and bevy_camera_follow_new (the destructor)
   read the tunnel and its steering function at 0x10 and 0x14 */
struct CPTN CPLCY_BASE {
    CPLCY_C_HEADER
    /* 0x10 */ struct TN *ptn;
    /* 0x14 */ struct TNFN *ptnfn;
    u8 unknown_0x18[0x88];
};

/* CPLOOK, the look policy, 0x58 bytes */
struct CPLOOK CPLCY_BASE {
    CPLCY_C_HEADER
    u8 unknown_0x10[0x10];
    /* 0x20 */ f32 u;  /* UpdateCplook's u */
    /* 0x24 */ f32 du; /* its du */
    /* 0x28 */ f32 field_0x28; /* InitCplook: 7.0 */
    /* 0x2C */ f32 fovMin;
    u8 unknown_0x30[4];
    /* 0x34 */ void *ambience; /* reference pointer (UpdateCplook's pamb); InitCplook and bevy_camera_looks_reset clear it;
                                  CM_Destruct releases it */
    /* 0x38 */ void *field_0x38; /* reference pointer, cleared and released the same way */
    u8 unknown_0x3C[0x1C];
};

/* CPLCYCAMOBJ, the policy of a camera object, 0x18 bytes: InitCplcyCamobj (vtable D_002CAB90) */
struct CPLCYCAMOBJ CPLCY_BASE {
    CPLCY_C_HEADER
    /* 0x10 */ struct LO *pcamobj; /* CplcyCamobj_Update: the camera object it follows (PosLoWorld, PmatLoWorld) */
    u8 unknown_0x14[0x4];
};

/* CPCLOSE, 0x40 bytes: func_00151208 (vtable D_002CD450, bevy_camera_looks_*) */
struct CPCLOSE CPLCY_BASE {
    CPLCY_C_HEADER
    u8 unknown_0x10[4];
    /* 0x14 */ s32 lookat; /* func_0012E460 frees it; bevy_camera_looks_activate stores it */
    u8 unknown_0x18[0x28];
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

/* CPPOLICY, 0x20 bytes: func_00151610 (vtable D_002CD408, bevy_camera_policy_*) */
struct CPPOLICY CPLCY_BASE {
    CPLCY_C_HEADER
    /* 0x10 */ struct CPHOLDER *holder;
    u8 unknown_0x14[0xC];
};

/* K30CAM, 0xD0 bytes: func_00150728 (vtable D_002CD498), bevy_classes_k30_cam_* */
struct K30CAM CPLCY_BASE {
    CPLCY_C_HEADER
    /* 0x10 */ s32 field_0x10; /* bevy_classes_k30_cam_150780 reads it as the target object */
    /* 0x14 */ s32 field_0x14;
    /* 0x18 */ f32 minDistance; /* bevy_classes_k30_cam_150ef0's minDistance */
    u8 unknown_0x1C[0x24];
    /* 0x40 */ s32 active; /* its own flag (bevy_classes_k30_cam_set, func_00150E60, func_00150EA0), not CPLCY::active */
    u8 unknown_0x44[0x3C];
    /* 0x80 */ s128 currentPosition; /* bevy_classes_k30_cam_150ef0 */
    /* 0x90 */ s128 currentTarget;
    /* 0xA0 */ f32 currentDistance;
    u8 unknown_0xA4[0x10];
    /* 0xB4 */ f32 field_0xB4; /* func_00150728: 7.0 */
    u8 unknown_0xB8[8];
    /* 0xC0 */ void *field_0xC0; /* reference pointers, cleared by bevy_classes_k30_cam_reset, released by CM_Destruct */
    /* 0xC4 */ void *field_0xC4;
    u8 unknown_0xC8[0x8];
};

/* CPLOOKAT, 0x18 bytes: InitCplcy, then vtable D_002CD378 (CM_Construct); ActivateCplookat stores its two arguments */
struct CPLOOKAT CPLCY_BASE {
    CPLCY_C_HEADER
    /* 0x10 */ s32 field_0x10; /* ActivateCplookat's second argument */
    /* 0x14 */ s32 field_0x14; /* ActivateCplookat's first */
};

struct CPATTACHSOURCE {
    u8 unknown_0x0[0x1BC];
    /* 0x1BC */ f32 field_0x1BC; /* ActivateCpattach copies it into the camera manager */
};

#ifndef __cplusplus
/* C view of cm.h's CM: the BASIC words CM_Construct clears and its vtable pointer, radFovTarget, and the policy members CM_Construct
   initialises (the same offsets as cm.h; each as its CPLCY header, which CM_Construct's init functions take) */
struct CM {
    /* 0x0 */ void *pframe;        /* BASIC::pframe */
    /* 0x4 */ void *psidebag;      /* BASIC::psidebag */
    u8 unknown_0x8[0x4];
    /* 0xC */ void *vtable;        /* CM_Construct: D_002CA4D0 */
    u8 unknown_0x10[0x14];
    /* 0x24 */ f32 radFovTarget;   /* CM::radFovTarget */
    u8 unknown_0x28[0x378];
    /* 0x3A0 */ struct CPLCY cpman;
    /* 0x3B0 */ struct CPLCY cptn;
    u8 unknown_0x3C0[0x90];
    /* 0x450 */ struct CPLCY cplook;
    u8 unknown_0x460[0x48];
    /* 0x4A8 */ struct CPLCY cplcyCamobj;
    u8 unknown_0x4B8[0x8];
    /* 0x4C0 */ struct CPLCY cpclose;
    u8 unknown_0x4D0[0x30];
    /* 0x500 */ struct CPLCY cppolicy;
    u8 unknown_0x510[0x10];
    /* 0x520 */ struct CPLCY k30cam;
    u8 unknown_0x530[0xC0];
    /* 0x5F0 */ struct CPLCY cpattach;
    /* 0x600 */ struct CPLCY cplookat;
};
#endif

#if defined(__mips__)
typedef char check_CPLCY_size[(sizeof(struct CPLCY) == 0x10) ? 1 : -1];
typedef char check_CPTN_size[(sizeof(struct CPTN) == 0xA0) ? 1 : -1];
typedef char check_CPLOOK_size[(sizeof(struct CPLOOK) == 0x58) ? 1 : -1];
typedef char check_CPLCYCAMOBJ_size[(sizeof(struct CPLCYCAMOBJ) == 0x18) ? 1 : -1];
typedef char check_CPCLOSE_size[(sizeof(struct CPCLOSE) == 0x40) ? 1 : -1];
typedef char check_CPPOLICY_size[(sizeof(struct CPPOLICY) == 0x20) ? 1 : -1];
typedef char check_K30CAM_size[(sizeof(struct K30CAM) == 0xD0) ? 1 : -1];
typedef char check_CPLOOKAT_size[(sizeof(struct CPLOOKAT) == 0x18) ? 1 : -1];
typedef char check_CPTN_ptn[((unsigned int)&((struct CPTN *)0)->ptn == 0x10) ? 1 : -1];
typedef char check_CPLOOK_ambience[((unsigned int)&((struct CPLOOK *)0)->ambience == 0x34) ? 1 : -1];
typedef char check_CPCLOSE_lookat[((unsigned int)&((struct CPCLOSE *)0)->lookat == 0x14) ? 1 : -1];
typedef char check_K30CAM_currentPosition[((unsigned int)&((struct K30CAM *)0)->currentPosition == 0x80) ? 1 : -1];
typedef char check_K30CAM_field_0xC4[((unsigned int)&((struct K30CAM *)0)->field_0xC4 == 0xC4) ? 1 : -1];
#endif

#ifdef __cplusplus
/* a C++ source that includes this header gets the camera manager too (cm.h includes this header first, so either order works) */
#include "cm.h"
#endif
#endif
