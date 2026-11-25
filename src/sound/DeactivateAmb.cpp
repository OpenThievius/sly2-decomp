#include "amb.h"
extern "C" {
s32 FFindDlEntry(void *, void *);
void RemoveDlEntry(void *, void *);
extern char B_003DD08C;
void DeactivateAmb(AMB *pamb) {
    if (FFindDlEntry(&B_003DD08C, pamb) != 0) {
        RemoveDlEntry(&B_003DD08C, pamb);
        pamb->Release();
    }
}
}
