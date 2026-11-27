#include "sw.h"
extern "C" {
extern SW B_003DD490;
int FSwLoadBusy(SW *);
void *PdescHubOfCurrentEpisode();
void RequestTransition(SW *, void *, int, int, int, int);
void bevy_jobs_162e38(JOB *pjob) {
    B_003DD490.pjobPending = pjob;
    if (FSwLoadBusy(&B_003DD490) == 0 && B_003DD490.pwarpActive == 0) {
        RequestTransition(&B_003DD490, PdescHubOfCurrentEpisode(), 0x189, -1, 0, -1);
    }
}
}
