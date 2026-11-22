/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

/* a copy request: size, source and destination words (our names, from CopyAb's arguments) */
struct COPYREQ {
    /* 0x0 */ u32 cb;
    /* 0x4 */ void *psrc;
    /* 0x8 */ void *pdst;
};

void CopyAb__FPvT0Ui(void *, void *, u32);

void func_001EC718(struct COPYREQ *req) {
    CopyAb__FPvT0Ui(req->pdst, req->psrc, req->cb);
}
