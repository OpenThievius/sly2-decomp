#include "sly2.h"
#include "amb.h"
extern "C" int func_00232500(int, int, int, int, int, int);
extern "C" void ApplyAmbParams(AMB *pamb)
{
    unsigned grf = pamb->grf;
    if ((grf & 0x70) == 0)
        return;
    int grfParam = 0;
    int vol;
    int pitch;
    if (grf & 0x10) {
        grfParam = 1;
        vol = (int)(pamb->volAudible * 1024.0f);
    }
    if (grf & 0x20)
        grfParam |= 4;
    if (grf & 0x40) {
        grfParam |= 8;
        pitch = (int)(pamb->pitch * 12.0f);
    }
    func_00232500(pamb->voice, grfParam, vol, pamb->pan, pitch, 0);
}
