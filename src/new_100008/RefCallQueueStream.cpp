// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct SND;
extern "C" BASIC *QueueStream(SND *, int);

extern "C" CRef RefCallQueueStream(SND *object, int count, CRef *args)
{
    int aotyp = 0x13;
    int id;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &id);
    refResult.SetBasic(QueueStream(object, id));
    return refResult;
}
