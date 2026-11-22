// SPDX-License-Identifier: GPL-3.0-or-later
#include "sohit.h"
struct ENTRY { char pad0[4]; void *aseg; void *sm; unsigned flags; };
extern "C" void RetractSmaRef(int *);
extern "C" void RetractAsegaHandle(int *);
extern "C" void ApplyAsegToHandle(float, float, void *, SO *, unsigned, int *);
extern "C" void func_001F1448(void *, SO *, int, unsigned, int *);
void func_0017F4C0(SOHIT *so, ENTRY *entry)
{
    RetractSmaRef(&so->hSma);
    RetractAsegaHandle(&so->hAsega);
    if (entry != 0) {
        ApplyAsegToHandle(0.0f, 1.0f, entry->aseg, so, entry->flags, &so->hAsega);
        func_001F1448(entry->sm, so, -1, entry->flags, &so->hSma);
    }
}
