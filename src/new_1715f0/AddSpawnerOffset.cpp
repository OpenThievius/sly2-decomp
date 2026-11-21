// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"

struct Spawner
{
    char pad0[0x98];
    int offsetCount;
    QW *offsets;
};

void AddSpawnerOffset(Spawner *spawner, QW offset)
{
    int index = spawner->offsetCount;
    if (index < 0x10) {
        QW *slot = (QW *)(index * sizeof(QW) + (uptr)spawner->offsets);
        spawner->offsetCount = index + 1;
        *slot = offset;
    }
}
