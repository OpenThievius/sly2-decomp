#include "types.h"
#include "lo.h"
struct OBJ : LO {
    u8 unknown_0x50[0xBC];
    int f10C; int f110; int f114; int f118; char a11C[0x40]; int f15C; char a160[4];
};
extern char B_003DD490[], B_002DEB30[];
extern "C" void TriggerRsmg(void *, int, void *, void *, int);
extern "C" void ApplyTaskStateRequests(void *, int, void *, void *);
extern "C" void StartJsg(int, int);

void func_00184130(OBJ *self, int jt)
{
    self->f10C = jt;
    self->PostMessage(6, self);
    TriggerRsmg(B_003DD490, self->f118, self->a11C, self, 1);
    ApplyTaskStateRequests(B_002DEB30, self->f15C, self->a160, self);
    self->HandleSpliceEvent(5, 0, 0, 0, 0);
    if (self->f114)
        StartJsg(self->f114, jt);
}
