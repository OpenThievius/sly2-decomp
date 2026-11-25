/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ASEG, an animation (an LO), and ASEGA, a playing handle on it (a BASIC: vtable at 0xC, sidebag at 0x4, a reference count at 0x10;
   slot 1 is Asega_AddRef and slot 2 Asega_Release, which the handle functions call). murray.h, sly.h, stepguard.h and wipe.h only
   forward-declare them. The Murray carry code reads paseg, tLocal and tLength (SetMurrayCarryState, UpdateMurrayCarry; the phase it
   keeps is tLocal / tLength), FillBlAmrsg_file tLocal; the aseg and aseg-asega modules read the rest (readers per field). C++ for the
   classes; a C source reads ASEGA's count through the C struct. */
#ifndef SLY2_ASEGA_H
#define SLY2_ASEGA_H
#include "types.h"
#ifdef __cplusplus
#include "lo.h"
#include "dl.h"
#include "act.h"

struct ACTASEG;

/* A channel of an ASEG (8 bytes, ASEG::achn): which object and which transform of it the animation drives. The low 20 bits are
   a signed object id (compared with ALO::oid), bits 20 to 29 the transform's index (a signed field), bit 30 marks a strip
   channel and bit 31 sends its curve to the act's second slot (PchnFindAseg tests them; BindAsegChn takes the id and index apart the same way);
   `panim` is the curve ApplyAseg hands the act. */
struct ASEGCHN {
    /* 0x0 */ u32 grf;
    /* 0x4 */ ASEGANIM *panim;
};

/* An animation curve object (its vtable is at offset 0): GSpeedSlotSoAseg calls its third virtual to sample the curve. */
struct ASEGANIM {
    virtual void Slot1();
    virtual void Slot2();
    virtual void GetValues(float t, float scale, float *pagOut, int zero); /* GSpeedSlotSoAseg: samples at the start and the end */
};

/* The object a part drives (its vtable is at offset 0): SnapAsega calls its second virtual on every part link each tick. */
struct ASEGSINK {
    virtual void Slot1();
    virtual void Slot2(int ntarget, int zero, float tLocal, float svtLocal); /* SnapAsega */
};

/* A part of an ASEG (0xC bytes, ASEG::apart): an object by id and the part index ApplyAseg hands its slot 44. */
struct ASEGPART {
    /* 0x0 */ s32 ipart;
    /* 0x4 */ s32 oid;
    /* 0x8 */ ASEGSINK *psink; /* ApplyAseg copies it to the link */
};

/* A keyed event of an ASEG (0x10 bytes), passed to HandleAsegaEvent. */
struct ASEGEVENT {
    u8 unknown_0x0[0x10];
};

struct ASEG : LO {
    /* 0x50 */ DL dlAsega;     /* InitAseg: InitDl(&dlAsega, 0x2C), the playing handles; ApplyAseg appends, SetAsegsvtMaster walks it */
    /* 0x5C */ s32 cchn;       /* PchnFindAseg, ApplyAseg */
    /* 0x60 */ ASEGCHN *achn;  /* PchnFindAseg, ApplyAseg */
    /* 0x64 */ s32 cpart;      /* ApplyAseg */
    /* 0x68 */ ASEGPART *apart; /* ApplyAseg */
    /* 0x6C */ s32 priorityAct; /* ApplyAseg: copied to each act's priority */
    /* 0x70 */ s32 handsOff;   /* ApplyAseg passes it to SetAsegaHandsOff */
    /* 0x74 */ f32 tLength;    /* SeekAsega (the shared asega.h's name) */
    /* 0x78 */ f32 svtMaster;  /* InitAseg (1.0), SetAsegsvtMaster, ApplyAseg copies it to the handle */
    u8 unknown_0x7C[0x4];
    /* 0x80 */ CLQ clqSpeed;   /* InitAseg (1, 0, 0), ApplyAseg */
    /* 0x8C is not written */
    u8 unknown_0x8C[0x4];
    /* 0x90 */ LM lmSpeed;     /* InitAseg (0, 1.0), ApplyAseg */
    /* 0x98 */ s32 cevent;     /* ApplyAseg */
    /* 0x9C */ ASEGEVENT *aevent; /* ApplyAseg */
    /* 0xA0 */ s32 iea;        /* ApplyAseg: the handle's current event index */
    /* 0xA4 */ f32 *paea;     /* reader: ReblendAsegbl (a blend aseg keeps its event frames here and copies them, rescaled, from its events aseg) */
    u8 unknown_0xA8[0x8];
    /* 0xB0 */ s32 field_0xB0; /* PostAsegLoad passes it to its queued callback when it is not 0 */
};

struct ASEGA : BASIC {
    /* 0x10 */ s32 cref;       /* Asega_AddRef, Asega_Release */
    /* 0x14 */ ASEG *paseg;
    /* 0x18 */ LO *paloRoot;   /* ApplyAseg */
    /* 0x1C */ f32 tLocal;
    /* 0x20 */ f32 tTarget;    /* SeekAsega, ApplyAseg */
    u8 unknown_0x24[0x8];
    /* 0x2C */ struct ASEGA *pasegaNext; /* the DLE in ASEG::dlAsega: SetAsegsvtMaster follows it */
    u8 unknown_0x30[0x4];
    /* 0x34 */ ACTASEG *pactFirst; /* SeekAsega, ApplyAseg */
    /* 0x38 */ struct PARTLINK *plink; /* ApplyAseg */
    /* 0x3C */ s32 grfapl;     /* ApplyAseg */
    /* 0x40 */ f32 svtLocal;   /* the playing rate: SeekAsega (svt * svtMaster * factor); ApplyAseg tests its sign; SnapAsega passes it to
                                  each link; UpdateAsega advances tLocal by it; func_00204E38, func_00204ED8 pass it to the curve */
    /* 0x44 */ f32 svt;        /* SeekAsega */
    /* 0x48 */ f32 svtMaster;  /* SeekAsega, ApplyAseg */
    /* 0x4C */ f32 factor;     /* SeekAsega; ApplyAseg stores the limited clqSpeed there */
    /* 0x50 */ s32 iea;        /* ApplyAseg */
    u8 unknown_0x54[0x4];
    /* 0x58 */ s32 handsOff;  /* SetAsegaHandsOff (an ASEGA function: it sets and clears the world's hands-off state as this changes) */
    /* 0x5C */ s32 field_0x5C; /* ApplyAseg (0) */
};

/* What ApplyAseg links on each handle for a part (0x14 bytes, from func_0012CE50). */
struct PARTLINK {
    /* 0x00 */ ASEGSINK *psink; /* SnapAsega calls its slot 2 with nTarget */
    /* 0x04 */ unsigned nTarget;
    /* 0x08 */ LO *plo;
    /* 0x0C */ s32 ipart;
    /* 0x10 */ PARTLINK *pnext;
};
#else
struct ASEGA {
    u8 unknown_0x0[0x10];
    /* 0x10 */ s32 cref;       /* Asega_AddRef */
};
#endif
#endif
