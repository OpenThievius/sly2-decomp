/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The movie sprites of src/font-break/ (Place/Start/Stop/Seek/Update/RefreshSpriteInstance, PlayRootSpriteLabel*, QueueSpriteInstanceSlots).
   SPRITE is the 0x30-byte record blotsprite.h calls BLOTSPRITE (clabel, cinstance, label list, instance list, transform): the same
   layout, with the fields these functions read added (stamp and stopped state at 0x10 to 0x20, the owning movie at 0x24, the root flag
   at 0x28, the transform typed as a 2D affine). SPRITELABEL (0x18 bytes) holds a label's keys, length, sprite and id, SPRITEINST
   (0x18 bytes) one playing instance, SLOT (0x70 bytes) one character slot of an instance. C++ only. */
#ifndef FBSPRITE_H
#define FBSPRITE_H
#include "types.h"
#include "rgba.h"
#include "blot.h"

struct AMB;
struct MOVIECHAR;
struct SPRITE;

/* the instance's ambient sound is held through a reference pointer (StopSpriteInstance clears it with VirtualRefPtr_Assign); reading it
   goes through the conversion operator */
struct AMBREF {
    AMB *pamb;
    operator AMB *() const { return pamb; }
};

/* a 2D affine transform (a, b, c, d: the 2x2 part; e, f: the translation), padded to a quadword */
struct AFFINE2D {
    f32 a, b, c, d, e, f;
    f32 unknown_0x18;
    f32 unknown_0x1C;
} __attribute__((aligned(16)));

/* one key of a label: its actions (func_002190F8 pauses the instance on action 7) */
struct SPRITEKEY {
    u8 unknown_0x0[7];
    /* 0x07 */ u8 caction;
    /* 0x08 */ u8 *aaction;
    u8 unknown_0xC[0x14];
};

/* a 64-bit clock value (g_2ddf18); kept in a struct because StopSpriteInstance copies it as a struct */
struct SPRITESTAMP {
    u64 value;
};

struct SPRITELABEL {
    u8 unknown_0x0[4];
    /* 0x04 */ SPRITEKEY *akey;     /* reader: func_002190F8 */
    /* 0x08 */ f32 dt;              /* the label's length: SeekSpriteInstanceFraction, SeekSpriteInstanceTime, UpdateSpriteInstance */
    /* 0x0C */ BLOT *pblot;         /* QueueSpriteInstanceSlots queues onto its list (sl, 0xFC) */
    /* 0x10 */ struct SPRITE *psprite; /* RefreshSpriteInstance, func_002190F8 */
    /* 0x14 */ s32 id;              /* PlayRootSpriteLabel, PlaceSpriteInstance */
};

/* one character slot of an instance (RefreshSpriteInstance fills the current transform and colours) */
struct SLOT {
    /* 0x00 */ RGBA rgbaAdd;
    /* 0x04 */ RGBA rgbaMul;
    u8 unknown_0x8[8];
    /* 0x10 */ AFFINE2D xf;
    /* 0x30 */ MOVIECHAR *pchar;
    /* 0x34 */ s32 maskMode;
    /* 0x38 */ f32 tFrom;
    /* 0x3C */ RGBA rgbaAddFrom;
    /* 0x40 */ RGBA rgbaMulFrom;
    /* 0x44 */ AFFINE2D *pxfFrom;
    /* 0x48 */ f32 tTo;
    /* 0x4C */ RGBA rgbaAddTo;
    /* 0x50 */ RGBA rgbaMulTo;
    /* 0x54 */ AFFINE2D *pxfTo;
    /* 0x58 */ s32 iinst;
    /* 0x5C */ f32 tUpdated;
    /* 0x60 */ u8 fTween;
    u8 unknown_0x61[7];
    /* 0x68 */ void *pslNext;
    u8 unknown_0x6C[4];
};

struct SPRITEINST {
    /* 0x00 */ s32 cslot;
    /* 0x04 */ SLOT *aslot;
    /* 0x08 */ s16 ilabel;          /* -1 when unused */
    /* 0x0A */ s16 ikeyNext;
    /* 0x0C */ f32 t;
    /* 0x10 */ s32 fPaused;
    /* 0x14 */ AMBREF ramb;
};

/* the movie a sprite belongs to, as a flat view of the BLOT (blot.h): asprite at 0x84, the world object and the transform at 0xF4 */
struct SPRITEMOVIE {
    u8 unknown_0x0[0x84];
    /* 0x84 */ struct SPRITE *asprite;
    u8 unknown_0x88[0x6C];
    /* 0xF4 */ void *plo;
    /* 0xF8 */ AFFINE2D *pxf;
};

struct SPRITE {
    /* 0x00 */ u16 clabel;
    u8 unknown_0x2[2];
    /* 0x04 */ SPRITELABEL *labels;
    /* 0x08 */ SPRITEINST *insts;
    u8 unknown_0xC[4];
    /* 0x10 */ SPRITESTAMP stamp;           /* g_2ddf18 when StopSpriteInstance saved the stopped state below */
    /* 0x18 */ f32 tStopped;
    /* 0x1C */ s32 ilabelStopped;
    /* 0x20 */ s32 ilabelPending;
    /* 0x24 */ SPRITEMOVIE *pmovie;
    /* 0x28 */ s32 fRoot;
    /* 0x2C */ AFFINE2D *pxf;
};
#endif
