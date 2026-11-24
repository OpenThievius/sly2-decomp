#include "jt.h"

extern "C" {
void StartAttach(void *, s32, s32, s32);

void SetJtAttach5(JT *arg0, s32 arg1) {
    if (arg1 != 0) {
        StartAttach(arg0->PvAttach(), 5, arg1, 0);
        return;
    }
    if (arg0->attachKind != 5) {
        return;
    }
    arg0->SetMode(0);
}

}
