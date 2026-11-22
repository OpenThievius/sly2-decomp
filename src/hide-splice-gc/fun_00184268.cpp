// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"
extern "C" {
void func_00183F08(struct ATTACHPT *);

void func_00184268(struct LIFTPT *lift) {
    func_00183F08(&lift->attachpt);
    lift->aref[0].oid = -1;
    lift->aref[1].oid = -1;
    lift->aref[2].oid = -1;
    lift->oidLast = -1;
    lift->attachpt.member.field_0x10 = -1;
    lift->attachpt.member.field_0x1C = 4;
}
}
