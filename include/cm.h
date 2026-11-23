/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CM, the camera manager, and CPLCY, the base of its camera policies. C++ only (include/cplcy.h has the C views).

   CM: one static global at 0x2DDF40 (B_002DDF40), built by CM_Construct (0x14D3D8) and torn down by CM_Destruct, which ends in
   BASIC_Destruct: a BASIC (lo.h) with its own vtable at 0x2CA4D0 (slots 1 to 6, slot 6 func_00114280). Its methods are the
   functions of retail's file 0x14D470-0x14FAC8 (src/new_14d1d0/new_14d1d0_14d470.cpp). Its policy members, 0x3A0 to 0x618, are
   the objects CM_Construct initialises in turn (InitCpman, InitCptn, InitCplook, InitCplcyCamobj, func_00151208, func_00151610,
   func_00150728, func_001518C8, InitCplcy) and InitCm resets at the same offsets: each starts with the CPLCY header and its own
   bytes follow as unknown (the derived classes are cplcy.h's C views: CPTN, CPLOOK, CPCLOSE, CPPOLICY, K30CAM).

   CPLCY: 0x10 bytes, three words and the vtable pointer at 0xC (g++ 2.95 puts it after the first virtual class's own fields, as
   lo.h explains). Every policy vtable (D_002CD570 for the base, InitCplcy) has seven slots after the type-info entry, declared
   here in slot order; a signature is written only where a matched caller shows it (RevokeCmPolicy, UpdateCmLast,
   bevy_camera_cm_14d650), the others are `void ()` placeholders.

   The field rule is lo.h's: a field is here when a method of the class reads it (the class is certain), with its readers.
   Names: `source:sly1` is TheOnlyZac/sly1's CM (CC0, THIRD_PARTY_NOTICES.md); the others are ours, from the readers. */
#ifndef SLY2_CM_H
#define SLY2_CM_H
#include "types.h"
#include "sly2.h"
#include "lo.h"

struct SO;
struct CMREGION; /* the object bevy_camera_cm_14e148 records: its body is local to its only reader's file (new_14d1d0_14d470.cpp) */

/* The camera's definition of its focus, 0x50 bytes: SO slot 50 (GetSoCpdefi) fills the first 0x40, GetCmCpdefi adds posAdjust.
   source:sly1 CPDEFI (posBase, vBase there) */
struct CPDEFI {
    /* 0x0 */ s32 grfcpd;          /* GetSoCpdefi */
    u8 unknown_0x4[0xC];
    /* 0x10 */ QW pos;             /* GetSoCpdefi; GetCmCpdefi adds the adjustment to it */
    /* 0x20 */ QW vel;             /* GetSoCpdefi */
    /* 0x30 */ f32 radHome;        /* CalcCmAdjust */
    /* 0x34 */ f32 sAdjust;        /* CalcCmAdjust */
    /* 0x38 */ f32 tMoveLast;      /* GetSoCpdefi */
    /* 0x3C */ s32 cfk;            /* GetSoCpdefi */
    /* 0x40 */ QW posAdjust;       /* GetCmCpdefi, AdjustCmCpdefi: pos plus CM::dposAdjust */
};

/* The fog function the renderer reads, 0x10 bytes: BuildCmFgfn fills it. source:sly1 FGFN */
struct FGFN {
    /* 0x0 */ f32 duFogBias;           /* FitRecipFunction's first result, biased by 8417280 */
    /* 0x4 */ f32 ruFog;               /* FitRecipFunction's second result */
    /* 0x8 */ f32 sNearFog;            /* CM::sNearFog */
    /* 0xC */ f32 duFogPlusClipBias;   /* duFogBias + 8192 */
};

/* A smoothing block for GSmoothA (the type its mangled name takes, GSmoothA__FffffP4SMPAPf); only InitCm writes it, 0x10 bytes */
struct SMPA {
    /* 0x0 */ f32 field_0x0;       /* InitCm: 0.5 */
    /* 0x4 */ s32 field_0x4;       /* InitCm: 0 */
    /* 0x8 */ f32 field_0x8;       /* InitCm: 0.1 */
    /* 0xC */ f32 field_0xC;       /* InitCm: 10.0 */
};

/* A colour, four bytes; read as one unaligned word (SetCmRgbaFog, InitCm) */
struct RGBA {
    u8 r, g, b, a;
};

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
    virtual void Update(CPDEFI *pcpdefi, void *pjoy); /* 6: UpdateCplcy; UpdateCmLast passes the focus's CPDEFI (or 0) and a pad:
                                                     B_002DFC00 (a JOY) or B_002E0D00 */
    virtual void Reset();                         /* 7: ResetCplcy; bevy_camera_cm_14d650 calls it on every record */
};

/* One policy record, 0x10 bytes: RevokeCmPolicy compares and copies them. source:sly1 CPR (psoFocus) */
struct CPR {
    /* 0x0 */ s32 cpp;             /* a CPP (enum CPP: tank.h and the sources that pass one) */
    /* 0x4 */ CPLCY *pcplcy;       /* RevokeCmPolicy, UpdateCmLast, bevy_camera_cm_14d650, func_0014F5F8, bevy_camera_cm_14f630 */
    /* 0x8 */ SO *psoFocus;        /* RevokeCmPolicy, UpdateCmLast */
    /* 0xC */ void *pv;            /* RevokeCmPolicy */
};

struct CM : BASIC {
    /* 0x10 */ struct CMREGION *pregion; /* bevy_camera_cm_14e148 records the region func_0014E078 ranks first; InitCm clears it */
    /* 0x14 */ s32 field_0x14;     /* bevy_camera_cm_14e148: the region's word 0xE0; InitCm: 0xFF */
    /* 0x18 */ f32 rMrdRatio;      /* SetCmMrdRatio; RecalcCmFrustrum divides it by radFov; InitCm: 1.0 */
    /* 0x1C */ f32 rMrd;           /* RecalcCmFrustrum: at least 1; InitCm: 1.0. source:sly1 rMRD */
    /* 0x20 */ f32 radFov;         /* RecalcCmFrustrum, SetCmFov, UpdateCmLast. source:sly1 radFOV */
    /* 0x24 */ f32 radFovTarget;   /* SetCmFov, UpdateCmLast, func_0014F5F8; ActivateCpattach, DeactivateCplcy (was field_0x24) */
    /* 0x28 */ f32 dradFov;        /* SetCmFov clears it; UpdateCmLast smooths radFov with it */
    /* 0x2C */ SMPA smpaFov;       /* UpdateCmLast passes it to GSmoothA; InitCm */
    /* 0x3C */ f32 rAspect;        /* RecalcCmFrustrum; InitCm: 1.2987015. source:sly1 */
    /* 0x40 */ f32 xScreenRange;   /* RecalcCmFrustrum. source:sly1 */
    /* 0x44 */ f32 yScreenRange;   /* RecalcCmFrustrum. source:sly1 */
    /* 0x48 */ f32 sRadiusNearClip; /* RecalcCmFrustrum. source:sly1 */
    /* 0x4C */ f32 sNearClip;      /* SetCmNearClip, RecalcCmFrustrum; ActivateCplcy saves it. source:sly1 */
    /* 0x50 */ f32 sFarClip;       /* SetCmFarClip, RecalcCmFrustrum. source:sly1 */
    u8 unknown_0x54[0xC];
    /* 0x60 */ MATRIX4 mat;        /* row 3 the position: SetCmPosMat, SetCmMat, func_0014F3C8, func_0014F4E0, func_0014E078; InitCm */
    u8 unknown_0xA0[0x60];
    /* 0x100 */ MATRIX4 matProj;   /* RecalcCmFrustrum (BuildSimpleProjectionMatrix). source:sly1 */
    u8 unknown_0x140[0x100];
    /* 0x240 */ f32 sNearFog;      /* SetCmNearFog, BuildCmFgfn; InitCm. source:sly1 */
    /* 0x244 */ f32 sFarFog;       /* SetCmFarFog, BuildCmFgfn; InitCm. source:sly1 */
    /* 0x248 */ f32 uFogMax;       /* SetCmUFogMax, BuildCmFgfn; InitCm. source:sly1 */
    /* 0x24C */ RGBA rgbaFog;      /* SetCmRgbaFog, InitCm. source:sly1 */
    /* 0x250 */ FGFN fgfn;         /* RecalcCmFrustrum (BuildCmFgfn). source:sly1 */
    /* 0x260 */ SO *psoCpdefi;     /* UpdateCmLast, GetCmCpdefi: the object cpdefi was read from */
    u8 unknown_0x264[0xC];
    /* 0x270 */ CPDEFI cpdefi;     /* UpdateCmLast, GetCmCpdefi */
    /* 0x2C0 */ QW dposAdjust;     /* ResetCmAdjust, AdjustCmCpdefi (sprung with vAdjust) */
    /* 0x2D0 */ VECTOR vAdjust;    /* ResetCmAdjust clears x, y, z; AdjustCmCpdefi */
    /* 0x2E0 */ QW field_0x2E0;    /* AdjustCmCpdefi springs it to zero (g_2a2dd0) or holds it */
    /* 0x2F0 */ VECTOR field_0x2F0; /* ResetCmAdjust clears x, y, z; AdjustCmCpdefi */
    /* 0x300 */ s32 fCut;          /* UpdateCmLast, SetResetFlag (at least 1), bevy_camera_cm_14d8d8 (at least 2). source:sly1 */
    /* 0x304 */ f32 field_0x304;   /* bevy_camera_cm_14d8d8 */
    /* 0x308 */ f32 field_0x308;   /* bevy_camera_cm_14d8d8 */
    /* 0x30C */ s32 ccpr;          /* RevokeCmPolicy, UpdateCmLast, bevy_camera_cm_14d650; InitCm. source:sly1 */
    /* 0x310 */ CPR acpr[8];       /* RevokeCmPolicy, UpdateCmLast (the first is the current policy). source:sly1 */
    /* 0x390 */ f32 tActivateCplcy; /* RevokeCmPolicy: the clock's time when it activates the new first policy. source:sly1 */
    u8 unknown_0x394[0xC];
    /* 0x3A0 */ CPLCY cpman;       /* InitCpman; InitCm sets it as the base policy (SetCmPolicy, CPP 0). source:sly1 */
    /* 0x3B0 */ CPLCY cptn;        /* the tunnel policy (cplcy.h's CPTN, 0xA0 bytes): InitCptn; SetTnTns sets it */
    u8 unknown_0x3C0[0x90];
    /* 0x450 */ CPLCY cplook;      /* the look policy (cplcy.h's CPLOOK, 0x58 bytes): InitCplook; Warp_Start revokes it;
                                      CM_Destruct releases its words 0x34 and 0x38. source:sly1 */
    u8 unknown_0x460[0x48];
    /* 0x4A8 */ CPLCY cplcyCamobj; /* 0x18 bytes: InitCplcyCamobj */
    u8 unknown_0x4B8[0x8];
    /* 0x4C0 */ CPLCY cpclose;     /* cplcy.h's CPCLOSE, 0x40 bytes: func_00151208 (vtable D_002CD450, bevy_camera_looks_*) */
    u8 unknown_0x4D0[0x30];
    /* 0x500 */ CPLCY cppolicy;    /* cplcy.h's CPPOLICY, 0x20 bytes: func_00151610 (vtable D_002CD408, bevy_camera_policy_*) */
    u8 unknown_0x510[0x10];
    /* 0x520 */ CPLCY k30cam;      /* cplcy.h's K30CAM, 0xD0 bytes: func_00150728; Warp_Start revokes it; CM_Destruct releases its
                                      words 0xC0 and 0xC4 */
    u8 unknown_0x530[0xC0];
    /* 0x5F0 */ CPLCY cpattach;    /* 0x10 bytes: func_001518C8 (vtable D_002CD3C0, ActivateCpattach); OnTankActive sets it */
    /* 0x600 */ CPLCY cplookat;    /* 0x18 bytes: InitCplcy, then vtable D_002CD378 (ActivateCplookat); func_001CBF90 sets it */
    u8 unknown_0x610[0x8];
    /* 0x618 */ f32 tJolt;         /* JoltCm: the clock's time; InitCm: -10.0. source:sly1 */
    /* 0x61C */ s32 nJolt;         /* JoltCm; InitCm: -1 */
    /* 0x620 */ f32 sStereo;       /* UpdateCmLast smooths it to sStereoTarget; bevy_camera_cm_14d650 clears it */
    /* 0x624 */ f32 sStereoTarget; /* UpdateCmLast; bevy_camera_cm_14d650: 10.0 */
};

extern "C" CM B_002DDF40; /* the camera manager */

#if defined(__mips__)
typedef char check_CPDEFI_size[(sizeof(CPDEFI) == 0x50) ? 1 : -1];
typedef char check_CPLCY_size[(sizeof(CPLCY) == 0x10) ? 1 : -1];
typedef char check_CPR_size[(sizeof(CPR) == 0x10) ? 1 : -1];
typedef char check_CM_radFovTarget[((unsigned int)&((CM *)0)->radFovTarget == 0x24) ? 1 : -1];
typedef char check_CM_cpdefi[((unsigned int)&((CM *)0)->cpdefi == 0x270) ? 1 : -1];
typedef char check_CM_acpr[((unsigned int)&((CM *)0)->acpr == 0x310) ? 1 : -1];
typedef char check_CM_cptn[((unsigned int)&((CM *)0)->cptn == 0x3B0) ? 1 : -1];
typedef char check_CM_cplook[((unsigned int)&((CM *)0)->cplook == 0x450) ? 1 : -1];
typedef char check_CM_k30cam[((unsigned int)&((CM *)0)->k30cam == 0x520) ? 1 : -1];
typedef char check_CM_cplookat[((unsigned int)&((CM *)0)->cplookat == 0x600) ? 1 : -1];
typedef char check_CM_sStereoTarget[((unsigned int)&((CM *)0)->sStereoTarget == 0x624) ? 1 : -1];
#endif
#endif
