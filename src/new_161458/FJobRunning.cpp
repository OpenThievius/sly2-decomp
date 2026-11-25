#include "job.h"
extern "C" {
int FSwLoadBusy(void *);
extern char B_003DD490;
int FJobRunning(JOB *self) { if (self->disabled == 0) { int s = self->cause; if (s == 2) return 0; if (s == 3) return 0; return FSwLoadBusy(&B_003DD490) == 0; } return 0; }
}
