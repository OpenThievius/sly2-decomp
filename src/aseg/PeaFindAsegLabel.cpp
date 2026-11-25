#include "asega.h"
/* A label event of an ASEG (an ASEGEVENT of kind 11, its id at 0x8) and the table PeaFindAsegLabel reads: a count at 0xA0, the events at 0xA4 */
struct ASEGLABEL { u8 unknown_0x0[0x4]; s32 eatyp; s32 id; u8 unknown_0xC[0x4]; };
struct ASEGLABELTABLE { u8 unknown_0x0[0xA0]; s32 count; ASEGLABEL *labels; };
extern "C" ASEGLABEL *PeaFindAsegLabel(ASEG *paseg, int id)
{
    ASEGLABELTABLE *ptable = (ASEGLABELTABLE *)paseg;
    for (int i = 0; i < ptable->count; i++) {
        ASEGLABEL *p = &ptable->labels[i];
        if ((p->eatyp == 11) & (p->id == id))
            return p;
    }
    return 0;
}
