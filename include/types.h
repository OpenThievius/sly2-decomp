/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Fixed-width types for the EE, one definition for every source (docs/PRESERVATION_AND_PORT.md, "Changes" 2).
   With the game's compilers int is 32 bits, long 64 and a TI-mode int 128 (a quadword in one register). */
#ifndef SLY2_TYPES_H
#define SLY2_TYPES_H
typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long s64;
typedef unsigned long u64;
typedef int s128 __attribute__((mode(TI)));
typedef unsigned int u128 __attribute__((mode(TI)));
typedef int QW __attribute__((mode(TI))); /* a quadword in one 128-bit register */
typedef float f32;
typedef double f64;
/* An integer that holds an address: where retail's code keeps a pointer in an integer (masks it, aligns it, tests it, stores it
   in an integer field) and a pointer type would change that code. The EE's pointers are 32 bits, so these are retail's s32 and
   u32; a port to 64-bit pointers makes them intptr_t and uintptr_t (docs/PORTING.md), as sly1-decomp's sptr and uptr. */
typedef s32 sptr;
typedef u32 uptr;
#endif
