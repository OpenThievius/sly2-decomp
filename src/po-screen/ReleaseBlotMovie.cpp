#include "blot.h"
extern "C" {
void ClearSl(SL *);
void ReleaseBlotMovie(BLOT *arg0) {
    BLOTSTREAM *temp_v0;
    arg0->field_0xF8 = 0;
    arg0->field_0x50 = 0;
    arg0->field_0x54 = 0;
    arg0->csprite = 0;
    arg0->asprite = 0;
    ClearSl(&arg0->sl);
    temp_v0 = arg0->pstream;
    temp_v0->start = 0;
    temp_v0->end = 0;
}
}
