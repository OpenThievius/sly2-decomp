#include "sly2.h"
#include "goals.h"
#include "jt.h"
extern "C" {
void func_001EEF70(void *);
void func_00146650(void *, int);
void func_001461F8(GOALPARTNERATTACK *self) {
    func_001EEF70(self);
    func_00146650(self, 0);
    JT *pjt = (JT *)self->pstep;
    pjt->SetFocus(4, (STEPGUARD *)self->ploTarget, 4, (STEPGUARD *)self->ploTarget);
    ((JT *)self->pstep)->fFocusBusy |= 1;
}
}
