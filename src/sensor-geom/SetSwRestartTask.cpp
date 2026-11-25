#include "sly2.h"
#include "job.h"
#include "sw.h"
extern int B_002DEB48;
void SetSwRestartTask(SW *psw, TASK *ptask)
{
    psw->ptaskRestart = ptask;
    if (ptask)
        B_002DEB48 = ptask->oid;
    else
        B_002DEB48 = -1;
}
