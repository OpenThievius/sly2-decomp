#include "job.h"
struct Toggle_1626C0 { int word0; int word4; int word8; int wordC; };
extern "C" {
int GrfOfState(int);
void AddJobToggle(JOB *job, int arg1, int arg2, int arg3, int arg4) {
    if (job->disabled == 0) {
        int index = job->ctoggle;
        if (index < 0x20) {
            Toggle_1626C0 *toggle = (Toggle_1626C0 *)job->atoggle + index;
            job->ctoggle = index + 1;
            toggle->word0 = arg1;
            toggle->word4 = arg3;
            toggle->word8 = GrfOfState(arg2);
            toggle->wordC = arg4;
        }
    }
}
}
