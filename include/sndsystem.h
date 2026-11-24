/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SNDSYSTEM, the sound system object (the singleton at B_003DD040): func_001FCD38 constructs it, InitSndSystem fills its volume tables,
   LoadSndFromBrx loads its banks and streams, ResetSnd clears it. Its two slot heaps at 0x1C and 0x34 are the emitters' (B_003DD05C,
   0x70-byte AMB slots) and the stream emitters' (B_003DD074, 0x3C0-byte slots). A field is here when two matched functions agree on
   its offset or a method of the class (constructor, loader, reset) touches it; readers listed. C++ only. */
#ifndef SLY2_SNDSYSTEM_H
#define SLY2_SNDSYSTEM_H
#include "types.h"
#include "dl.h"
#include "sw.h"
#include "clq.h"
#include "bytes8.h"
#include "streamamb.h"

/* a 0x40-byte object id: eight 8-byte halves compared by two of their words (OidEqual) */
struct OIDB { BYTES8 q[8]; };

/* a stream's entry: LoadSndFromBrx builds the list at SNDSYSTEM::ents, FFindLevel reads one's level */
struct SNDENT {
    OIDB oid;                           /* LoadSndFromBrx stores the picked track's id */
    /* 0x40 */ s32 id;                  /* func_001FCFA0 matches it */
    /* 0x44 */ struct SNDENT *next;
    /* 0x48 */ s32 ref48;               /* LoadSndFromBrx */
    /* 0x4C */ s32 f4C;                 /* LoadSndFromBrx */
    /* 0x50 */ f32 level;               /* LoadSndFromBrx; FFindLevel returns it */
    /* 0x54 */ s32 count;               /* LoadSndFromBrx: bytes of data / 8 */
    /* 0x58 */ void *data;              /* LoadSndFromBrx */
};

/* a record of SNDSYSTEM::recs (0x48 bytes): LoadSndFromBrx fills the id, then reads the object id into its first 0x40 bytes */
struct SNDREC {
    u8 unknown_0x0[0x40];
    /* 0x40 */ s32 id;                  /* func_001FCFF8 matches it */
    /* 0x44 */ struct SNDREC *next;
};

struct SNDSYSTEM {
    /* 0x00 */ s32 field_0x0;           /* func_001FCD38 clears it */
    /* 0x04 */ s32 field_0x4;           /* func_001FCD38 clears it */
    u8 unknown_0x8[4];
    /* 0x0C */ void *vtable;            /* func_001FCD38 */
    /* 0x10 */ s32 field_0x10;          /* func_001FCD38 clears it */
    /* 0x14 */ s32 field_0x14;          /* ResetSnd clears it */
    /* 0x18 */ s32 nmap;                /* LoadSndFromBrx stores the map's size; ResetSnd sets -1; func_001FD028 bounds the index by it */
    /* 0x1C */ SLOTHEAP heapAmb;        /* func_001FCD38 (0x70-byte slots), ResetSnd; PvAllocAmb, FreeAmb */
    /* 0x34 */ SLOTHEAP heapStreamAmb;  /* func_001FCD38 (0x3C0-byte slots), ResetSnd; PvAllocStreamAmb, FreeStreamAmb */
    /* 0x4C */ DL dl;                   /* func_001FCD38 (InitDl, 0x38 = ibDle), ResetSnd (ClearDl) */
    /* 0x58 */ s32 field_0x58;          /* func_001FCD38 clears it; InitStreamAmb pauses a new stream emitter while it is set */
    /* 0x5C */ s32 field_0x5C;          /* ResetSnd clears it */
    /* 0x60 */ s32 field_0x60;          /* ResetSnd clears it */
    /* 0x64 */ s32 imix;                /* UpdateSndMix sets it (0 to 2: which of the three mixes is audible); func_001FEED0 draws only while it is 0 */
    /* 0x68 */ s32 field_0x68;          /* func_001FCD38 and ResetSnd set 3 */
    /* 0x6C */ s32 started;             /* func_001FDA48 sets it and schedules the hit-effect callback once; func_001FCF70 clears it */
    /* 0x70 */ f32 progress;            /* func_001FDA48 reads it (the curves at fitA/fitB are evaluated at it); func_001FCF70 stores it */
    /* 0x74 */ s32 field_0x74;          /* ResetSnd hands its address to ReplaceHitFx (a hit-effect slot) */
    u8 unknown_0x78[8];
    /* 0x80 */ CLQ fitA;                /* func_001FCD38 (FitClq) */
    u8 unknown_0x8C[4];
    /* 0x90 */ CLQ fitB;                /* func_001FCD38 (FitClq) */
    u8 unknown_0x9C[4];
    /* 0xA0 */ s32 field_0xA0;         /* func_001FDBA8 sets 1 once and schedules func_001FCF88; func_001FCF88 clears it */
    /* 0xA4 */ s32 field_0xA4;         /* func_001FCF88 stores its first argument */
    /* 0xA8 */ OIDB oid;                /* LoadSndFromBrx stores the bank's object id here */
    /* 0xE8 */ s32 bank;                /* LoadSndFromBrx unloads it when the id changes (LoadSndBank loads it) */
    /* 0xEC */ SNDENT *ents;            /* LoadSndFromBrx; func_001FCFA0, FFindLevel; ResetSnd clears it */
    /* 0xF0 */ SNDREC *recs;            /* LoadSndFromBrx; func_001FCFF8, func_001FD080; ResetSnd clears it */
    /* 0xF4 */ void *amb;               /* LoadSndFromBrx stores the stream object-id header; func_001FD080 compares it; ResetSnd clears it */
    /* 0xF8 */ s32 nbank;               /* LoadSndFromBrx; ResetSnd clears it */
    /* 0xFC */ s32 *banks;              /* LoadSndFromBrx; func_001FD028, func_001FD070 */
    /* 0x100 */ s32 *map;               /* LoadSndFromBrx; func_001FD028 */
    /* 0x104 */ s32 field_0x104;        /* func_001FCD38 clears it */
    /* 0x108 */ f32 aw[3];              /* UpdateSndMix: the weight of each mix; ResetSnd clears them */
    /* 0x114 */ CLQ clqA;               /* func_001FCD38 */
    /* 0x120 */ CLQ clqB;               /* func_001FCD38 */
    /* 0x12C */ CLQ clqC;               /* func_001FCD38 */
    /* 0x138 */ s32 field_0x138;        /* ResetSnd clears it */
    /* 0x13C */ f32 grid[8][4];         /* InitSndSystem sets all 1.0; InitStreamAmb reads grid[2][kind] (the volume of a stream's kind) */
    /* 0x1BC */ f32 field_0x1BC;        /* InitSndSystem sets 1.0 */
    /* 0x1C0 */ f32 mix[4];             /* InitSndSystem sets all 1.0 */
    /* 0x1D0 */ s32 nstream;           /* LoadSndFromBrx; ResetSnd clears it */
    /* 0x1D4 */ s32 streams[6];         /* LoadSndFromBrx (-1 for unused) */
    u8 unknown_0x1EC[4];
    /* 0x1F0 */ s64 now;                /* InitSndSystem stores the tick count; func_001FC878 */
    /* 0x1F8 */ s64 prev;               /* InitSndSystem stores the tick count; func_001FC878 */
    union {
        s32 field_0x200;                /* func_001FCD38 clears it; ResetSnd hands its address to func_00259B48 */
        STREAMAMB *pambStream;          /* the current stream's emitter: UpdateSnd, StartStream, StopStream, TStream */
    };
    union {
        struct {
            s32 field_0x204;            /* ResetSnd clears it; the number of stacked stream emitters (UpdateSnd, UpdateSndMix, QueueStream) */
            union {
                s32 words[8];           /* func_001FCD38 and ResetSnd clear them */
                STREAMAMB *queue[8];    /* the queue of stream emitters QueueStream fills, func_001FE478 takes one from */
            };
        };
        STREAMAMB *apamb[9];            /* the stack: apamb[field_0x204] is the top one (index 0 overlaps the count) */
    };
    union {
        s32 field_0x228;                /* func_001FCD38 clears it; LoadSndFromBrx and ResetSnd hand its address to func_00259B48 */
        STREAMAMB *pambC;               /* UpdateSnd pauses and continues it with the others */
    };
    /* 0x22C */ struct LO *aplo[6];     /* StartStream fills, StopStream releases and clears them (ResetSnd clears them) */
    /* 0x244 */ s32 icue;               /* StartStream clears it; StopStream and UpdateStreamCues step it */
    /* 0x248 */ f32 elapsed;            /* StartStream clears it; UpdateStreamCues */
    /* 0x24C */ f32 total;              /* StartStream clears it; UpdateStreamCues, TStream */
};
#endif
