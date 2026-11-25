#include "job.h"
extern "C" int FTaskPrerequisitesDone(TASK *ptask)
{
    int result = 1;
    int index = 0;
    if (index < ptask->cprereq) {
        TASK **ppreq = ptask->aprereq;
        do {
            TASK *preq = *ppreq;
            int state = preq->state;
            result = 0;
            if (state >= 2 || (state == 1 && preq->field_0x6C != 0))
                result = 1;
            ppreq++;
            index++;
            if (result == 0)
                break;
        } while (index < ptask->cprereq);
    }
    return result;
}
