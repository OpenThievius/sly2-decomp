#include "sly2.h"
#include "job.h"
#include "sw.h"
extern int B_002DEB44;
void SetSwCurrentTask(SW *psw, TASK *ptask)
{
    psw->ptaskCurrent = ptask;
    if (ptask)
        B_002DEB44 = ptask->oid;
    else
        B_002DEB44 = -1;
}
