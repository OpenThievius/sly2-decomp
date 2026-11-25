#include "types.h"
struct Game_162E38 { u8 unknown_0x0[0x3B18]; int pending; u8 unknown_0x3B1C[0x3C84 - 0x3B1C]; int busy; };
extern "C" {
extern Game_162E38 B_003DD490;
int FSwLoadBusy(Game_162E38 *);
void *PdescHubOfCurrentEpisode();
void RequestTransition(Game_162E38 *, void *, int, int, int, int);
void bevy_jobs_162e38(int arg0) {
    B_003DD490.pending = arg0;
    if (FSwLoadBusy(&B_003DD490) == 0 && B_003DD490.busy == 0) {
        RequestTransition(&B_003DD490, PdescHubOfCurrentEpisode(), 0x189, -1, 0, -1);
    }
}
}
