// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "jsg.h"

struct LO;
struct TN;
/* a record of the node's list (JSGE of src/stepguard-jsg/AddJsgContext_file.cpp): its kind, async flag, then the first argument, the key */
struct SEQNODE_KEY {
    /* 0x0 */ s32 jsgek;
    /* 0x4 */ s32 fAsync;
    u8 unknown_0x8[0x8];
    /* 0x10 */ int key;           /* arg[0].n there */
};
/* a sequence node; the members up to 0xE0 are those AddJsgContext_file.cpp's SEQNODE reads (Seqnode_AddRef/Release, RunSeqnode and the
   StartNextSeqnodeRecord family), the same object; `keyed` is its precFirst */
struct SEQNODE {
    /* 0x0 */ void *pframe;
    /* 0x4 */ void *psidebag;
    u8 unknown_0x8[0x4];
    /* 0xC */ void *vt;
    /* 0x10 */ s32 cref;
    /* 0x14 */ LO *psw;
    /* 0x18 */ LO *ploCtx;
    /* 0x1C */ LO *plo1C;
    /* 0x20 */ LO *plo20;
    /* 0x24 */ LO *psubject;
    /* 0x28 */ SEQNODE_KEY *keyed;
    /* 0x2C */ SEQNODE_KEY *precLast;
    /* 0x30 */ SEQNODE_KEY *precCur;
    /* 0x34 */ float rClock;
    /* 0x38 */ int fHandsOff;
    /* 0x3C */ int grfHandsOff;
    /* 0x40 */ SEQNODE_KEY *precDrive;
    /* 0x44 */ LO *ploDrive;
    /* 0x48 */ int fVjoyHold;
    /* 0x4C */ LO *pasega;
    /* 0x50 */ LO *pjsg;
    /* 0x54 */ LO *pjtPose;
    /* 0x58 */ LO *psma;
    /* 0x5C */ int fSmaCur;
    /* 0x60 */ LO *ploShown;
    /* 0x64 */ LO *ploSw;
    /* 0x68 */ SEQNODE_KEY *precStream;
    /* 0x6C */ TN *ptn;
    /* 0x70 */ int fTnAdded;
    /* 0x74 */ LO *ploLook;
    /* 0x78 */ float sCrv78;
    /* 0x7C */ float sCrv7C;
    /* 0x80 */ float tCam;
    u8 unknown_0x84[0xC];
    /* 0x90 */ int field_0x90;
    u8 unknown_0x94[0x8];
    /* 0x9C */ int fCamMove;
    /* 0xA0 */ LO *pjtBinoc;
    /* 0xA4 */ int cattach;
    /* 0xA8 */ LO *aploAttach[4];
    /* 0xB8 */ int an1Attach[4];
    /* 0xC8 */ int an2Attach[4];
    /* 0xD8 */ LO *ploD8;
    /* 0xDC */ LO *ploDC;
    /* 0xE0 */ int fE0;
    /* 0xE4 */ SEQNODE *next;     /* the DL link: PseqnodeFind walks JSG::dlSeqnode through it */
};

SEQNODE *PseqnodeFind(JSG *owner, int key, SEQNODE *skip) {
    VECTOR local;
    SEQNODE *node;
    for (node = (SEQNODE *)owner->dlSeqnode.head; node != 0; node = node->next) {
        if (node != skip && node->keyed->key == key)
            return node;
    }
    return 0;
}
