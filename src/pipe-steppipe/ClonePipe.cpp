// SPDX-License-Identifier: GPL-3.0-or-later
#include "pipe.h"

extern "C" {
void CloneCrv(CRV *);

void ClonePipe(PIPE *pipe) {
    BYTES8 saved;

    saved = pipe->kept;
    CloneCrv(pipe);
    pipe->kept = saved;
}
}
