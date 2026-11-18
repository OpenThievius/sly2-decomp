// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "alloc.h"
#include "dl.h"
#include "lo.h"
void *memset(void *, int, unsigned int);
struct OBSTACLEGROUP : LO {
    u8 pad50[0x10];
    float mat[16];
    u8 padA0[0x40];
    s32 field_0xE0;
    s32 field_0xE4;
    u8 padE8[4];
    float *mpicv;
    void *field_0xF0;
    void *field_0xF4;
    u8 padF8[0xC8];
    s32 field_0x1C0;
    u8 pad1C4[0x14];
    s32 field_0x1D8;
    u8 pad1DC[0xC];
    s32 field_0x1E8;
    void *field_0x1EC;
};
extern "C" OBSTACLEGROUP *PloNew(int, int, int, int);
extern "C" void *PvAllocSwImpl__Fi(ALLOCREQ *);
extern "C" void AppendDlEntry(DL *, void *);
extern "C" void RemoveDlEntry(DL *, void *);
extern DL B_003E1A40;

extern "C" OBSTACLEGROUP *PobstacleGroupAlloc()
{
    OBSTACLEGROUP *group = (OBSTACLEGROUP *)B_003E1A40.head;
    if (group == 0) {
        int index = 0;
        do {
            OBSTACLEGROUP *fresh = PloNew(0xE, 0, 0x2CD, -1);
            float *pmat = fresh->mat;
            fresh->field_0xE0 = 0;
            fresh->field_0xE4 = 1;
            fresh->field_0x1C0 = 1;
            memset(pmat, 0, 0x40);
            pmat[15] = 1.0f;
            pmat[10] = 1.0f;
            pmat[5] = 1.0f;
            pmat[0] = 1.0f;
            ALLOCREQ request;
            request.cb = 0x80;
            request.cbAlign = 0x10;
            fresh->mpicv = (float *)PvAllocSwImpl__Fi(&request);
            for (int icv = 0; icv < 0x20; icv++)
                fresh->mpicv[icv] = (float)icv;
            request.cb = 0x80;
            request.cbAlign = 0x10;
            fresh->field_0xF0 = PvAllocSwImpl__Fi(&request);
            index++;
            request.cb = 0x200;
            request.cbAlign = 0x10;
            fresh->field_0xF4 = PvAllocSwImpl__Fi(&request);
            request.cb = 0x1F0;
            request.cbAlign = 0x10;
            fresh->field_0x1EC = PvAllocSwImpl__Fi(&request);
            fresh->Remove();
            AppendDlEntry(&B_003E1A40, fresh);
        } while (index < 0x10);
        group = (OBSTACLEGROUP *)B_003E1A40.head;
    }
    RemoveDlEntry(&B_003E1A40, group);
    group->field_0x1E8 = -1;
    group->Add();
    group->field_0x1D8 = 0;
    return group;
}
