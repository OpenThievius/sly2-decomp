#include "sly2.h"
#include "goals.h"
#include "jt.h"
extern "C" {
void func_001EEF70(void *);
void func_00146158(void *, int);
void func_00145D00(GOALPARTNERATTACK *self) {
    func_001EEF70(self);
    func_00146158(self, 0);
    JT *pjt = (JT *)self->pstep;
    pjt->SetFocus(4, (STEPGUARD *)self->ploTarget, 4, (STEPGUARD *)self->ploTarget);
    ((JT *)self->pstep)->fFocusBusy |= 1;
}
}
