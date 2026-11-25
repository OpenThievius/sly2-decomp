#include "amb.h"
#include "sly2.h"
void SetAmbGrf(AMB*, int, int);
void StopAmb(AMB* a, float v)
{
    a->fadeSeconds = v;
    SetAmbGrf(a, 0x1FFF, 8);
}
