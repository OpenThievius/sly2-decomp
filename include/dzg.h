/* SPDX-License-Identifier: GPL-3.0-or-later */
/* DZ and DZG, the inequality solver of src/dl-dzg/ (func_0011A550 and the rest of that file) and src/dmas-dzg/ (InitDzg, SolveDzg):
   both sources declared their own copy, this one holds the union of their fields (offsets agree). DZ (0x28 bytes) is one inequality, DZG
   (0x64 bytes: the mangled names EnforceDzgDz__FP3DZGP2DZ and SolveDzg__FP3DZGiiPP2XPPiPPP2SO take it) the solver, its four lists, its
   matrix and, from 0x50, what InitDzg adds on top of func_0011A550 (the constraint counts and arrays). C++ only. */
#ifndef SLY2_DZG_H
#define SLY2_DZG_H
#include "types.h"
#include "dl.h"

struct DZ {
    /* 0x00 */ s32 dzk;        /* SolveDzgPrefilled (dl-dzg), SolveDzg: 1 moves it from the uncategorised list to the positive one */
    /* 0x04 */ f32 lo;         /* EnforceDzgDz: the lower bound of sdv */
    /* 0x08 */ f32 hi;         /* the upper bound (SolveInequalities stores sfMax) */
    /* 0x0C */ f32 sdv;        /* ClearDzgSolution clears it */
    /* 0x10 */ f32 sf;         /* SolveDzgPrefilled and SolveDzg pick the uncategorised one with the most negative; ClearDzgSolution clears it; EnforceDzgDz moves it */
    /* 0x14 */ f32 db;         /* EnforceDzgDz: the change of sf per unit step */
    /* 0x18 */ f32 *row;       /* its row of the matrix (SolveInequalities fills it); SolveDzg: null means FillDzgDz has not run for the row */
    u8 unknown_0x1C[4];
    /* 0x20 */ union {
        DLE dle;                /* the entry in one of the DZG's lists */
        struct { DZ *next; DZ *prev; };
    };
};

struct DZG {
    /* 0x00 */ s32 cdzMax;
    /* 0x04 */ s32 cdz;        /* the number of inequalities */
    /* 0x08 */ DZ *adz;
    /* 0x0C */ DL dlPos;       /* EnforceDzgDz's active set */
    /* 0x18 */ DL dlZero;      /* at the lower bound */
    /* 0x24 */ DL dlMax;       /* at the upper bound */
    /* 0x30 */ DL dlUncat;     /* not yet put in a list */
    /* 0x3C */ s32 cdzPos;     /* the length of dlPos */
    /* 0x40 */ f32 *aagPos;    /* the matrix of the active set */
    /* 0x44 */ f32 *aagPosCrout; /* its decomposition */
    /* 0x48 */ f32 *asdv;      /* the right-hand side */
    /* 0x4C */ f32 *adsfPos;   /* the solution */
    /* 0x50 */ s32 cxp;        /* InitDzg */
    /* 0x54 */ s32 axp;
    /* 0x58 */ s32 cso;
    /* 0x5C */ s32 apso;
    /* 0x60 */ void *axpd;
};
#endif
