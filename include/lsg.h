/* SPDX-License-Identifier: GPL-3.0-or-later */
/* LSG, a line segment of an edge clipped against geometry (0x60 bytes): both ends' positions, normals, parameters and face indices.
   The clippers (ClsgClipEdgeTo*) fill an array of them and ClsgMergeAlsg merges two arrays. Layout from the readers that agree:
   ClsgMergeAlsg and ScoreSafePoint (the whole record: apos, anormal, as, unk48, aiface, pedge), ClsgClipEdgeToObstacle's callers
   (PobstacleFindEdgeBlocker reads as[0] and as[1] at 0x40 and 0x44; func_001BD560 reads apos[0], typed VECTOR there), MatchJtXmgRail
   (apos[1] at 0x10) and func_001C0B50 (apos[0], apos[1]). C++ only. */
#ifndef SLY2_LSG_H
#define SLY2_LSG_H
#include "types.h"

struct LSG {
    /* 0x00 */ QW apos[2];     /* the two ends: ClsgMergeAlsg, ScoreSafePoint, MatchJtXmgRail (apos[1]), func_001C0B50 */
    /* 0x20 */ QW anormal[2];  /* ClsgMergeAlsg, ScoreSafePoint */
    /* 0x40 */ f32 as[2];      /* the clip parameter of each end: ClsgMergeAlsg, ScoreSafePoint, PobstacleFindEdgeBlocker (u at entry and exit) */
    /* 0x48 */ s32 unk48;      /* ClsgMergeAlsg, ScoreSafePoint */
    /* 0x4C */ s32 aiface[2];  /* ClsgMergeAlsg, ScoreSafePoint */
    /* 0x54 */ void *pedge;    /* ClsgMergeAlsg, ScoreSafePoint, RecalcSw (sw/FreeSwMqList_file) */
    u8 unknown_0x58[0x8];
};
#endif
