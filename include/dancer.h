/* SPDX-License-Identifier: GPL-3.0-or-later */
/* DANCER, the rhythm minigame's dancing character: a STEP (UpdateDancer calls UpdateStep on it; its size 0x2C0 is where the
   fields start). Its moves are keyed by a button; each has three steps that name an animation by object id, resolved to the
   animation by ResolveDancerMoves (PaloFindDancerAnim) and played by PlayDancerMove. Its size is not known. */
#ifndef SLY2_DANCER_H
#define SLY2_DANCER_H
#include "step.h"
#include "asega.h"

struct DANCERSTEP {
    /* 0x0 */ s32 oid;      /* AddDancerMove sets it, ResolveDancerMoves and PlayDancerMove read it (-1 = none) */
    /* 0x4 */ void *paseg;  /* the animation ResolveDancerMoves finds for the id; PlayDancerMove plays it */
    /* 0x8 */ u32 grfAnim;  /* AddDancerMove sets it; PlayDancerMove passes it to PlayDancerAnim as flags */
};

struct DANCERMOVE {
    /* 0x0 */ s32 btn;                /* AddDancerMove sets it; PlayDancerMove matches it (or tests it as a pad button) */
    /* 0x4 */ DANCERSTEP astep[3];    /* the three steps; AddDancerMove, ResolveDancerMoves, PlayDancerMove */
};

struct DANCER : STEP {
    /* 0x2C0 */ void *pasegIdle;       /* UpdateDancer plays it when the current animation is gone */
    /* 0x2C4 */ s32 cmove;             /* AddDancerMove (bounded by 8), ResolveDancerMoves, PlayDancerMove */
    /* 0x2C8 */ DANCERMOVE amove[8];   /* the same functions */
    /* 0x408 */ ASEGA *pasega;         /* the animation handle: UpdateDancer, PlayDancerAnim (as its address), PostDancerLoad's callers */
    /* 0x40C */ s32 fMove;             /* UpdateDancer (clears it, tests it before it starts a move) */
};
#endif
