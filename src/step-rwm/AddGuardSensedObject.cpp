// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
extern "C" void *memmove(void *, const void *, unsigned int);
struct CLOCK_2085D0 { float t; float dt; };
extern "C" CLOCK_2085D0 g_2dded0;

extern "C" SENSORENTRY *PentryFindSensorLo(SENSOR *list, LO *plo);

// Retail keeps the found entry, the count, the insertion index and the entry address in one
// callee-saved register ($s0): every step (subtract the tail, scale by 16, add the 0x100 array
// offset, add the list) writes it in place, so the source reuses one word-sized slot variable.
// The last step goes through an inline helper: written in place (`slot = list + slot`) GCC swaps
// the operands (`addu s0, s0, a0`); retail has the list first. The time is read from the clock
// struct (Clock_135248 elsewhere): as a plain float its load is hoisted above the stores.
static inline unsigned int OffsetInList(SENSOR *list, unsigned int offset)
{
    return (uptr)list + offset;
}

extern "C" int AddGuardSensedObject(STEPGUARD *guard, LO *plo, int append)
{
    if (plo != 0) {
        if (plo == guard)
            return 0;
        unsigned int slot = 0;
        if (append == 0)
            slot = (uptr)PentryFindSensorLo(guard->psensor, plo);
        if (slot != 0)
            return 0;
        SENSOR *list = guard->psensor;
        slot = list->centry;
        if (slot >= 8) {
            if (append != 0)
                return 0;
            int tail = guard->csensed;
            if (tail > 0) {
                guard->csensed = tail - 1;
                slot = 8;
                slot -= tail;
                slot *= sizeof(SENSORENTRY);
                slot += 0x100;
                slot = OffsetInList(list, slot);
                memmove((SENSORENTRY *)slot + 1, (SENSORENTRY *)slot, (tail - 1) * sizeof(SENSORENTRY));
            } else {
                return 0;
            }
        } else if (append != 0) {
            slot = (uptr)&list->aentry[slot];
        } else {
            int tail = guard->csensed;
            slot -= tail;
            slot *= sizeof(SENSORENTRY);
            slot += 0x100;
            slot = OffsetInList(list, slot);
            memmove((SENSORENTRY *)slot + 1, (SENSORENTRY *)slot, tail * sizeof(SENSORENTRY));
        }
        SENSORENTRY *entry = (SENSORENTRY *)slot;
        entry->plo = plo;
        entry->state = 0;
        entry->tState = g_2dded0.t;
        guard->psensor->centry++;
        return 1;
    }
    return 0;
}
