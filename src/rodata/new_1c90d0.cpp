// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A77C0-0X2A77D0 (piece rodata/new_1c90d0). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: ClonePool_AddLoGrfEntry, Carry_SetState.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void ClonePool_AcquireLeaseCallback();
void Carry_UpdateReach_thunk();
}

// data-ok: typed from ClonePool_AddLoGrfEntry (a pointer to member function, non-virtual, ClonePool_AcquireLeaseCallback), retail's bytes at 0X2A77C0
extern const PMF D_002A77C0 = {0, -1, {ClonePool_AcquireLeaseCallback}};

// data-ok: typed from Carry_SetState (a pointer to member function, non-virtual, Carry_UpdateReach_thunk), retail's bytes at 0X2A77C8
extern const PMF g_2a77c8 = {0, -1, {Carry_UpdateReach_thunk}};
