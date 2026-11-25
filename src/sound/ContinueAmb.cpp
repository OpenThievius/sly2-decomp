#include "amb.h"
extern "C" void SetAmbGrf(struct AMB *, unsigned short, unsigned short);
extern "C" void ContinueAmb(AMB *pamb)
{
    pamb->cPause--;
    if (pamb->cPause == 0) SetAmbGrf(pamb, 6, 4);
}
