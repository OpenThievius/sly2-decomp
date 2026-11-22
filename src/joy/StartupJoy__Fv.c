/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "joy.h"

struct CODELIST;
void InitCodes(struct CODELIST *codes);
void InitJoy(struct JOY *joy, s32 port, s32 slot);
void UpdateGrfjoytFromGrfusr__Fv(void);
s32 scePadInit(s32 mode);
extern struct CODELIST B_002DDEC0;
extern struct JOY B_002DFC00;

void StartupJoy__Fv(void) {
    UpdateGrfjoytFromGrfusr__Fv();
    scePadInit(0);
    InitJoy(&B_002DFC00, 0, 0);
    InitCodes(&B_002DDEC0);
}
