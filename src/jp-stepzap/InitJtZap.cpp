#include "jtzap.h"
void InitJtZap(JTZAP *self, JT *pjt)
{
    self->pjt = pjt;
    self->state = -1;
    self->flash = -1;
    self->dtFlash = 2.0f;
    self->field_0xC = 0x28;
}
