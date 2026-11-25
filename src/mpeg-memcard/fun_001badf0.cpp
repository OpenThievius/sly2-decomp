#include "sly2.h"
#include "stgswitch.h"
/* a touch the world reports to the switch: who touched it, the hit kind and the flag bits (upper word at 0x44) */
struct CONTACT { LO *toucher; u8 unknown_0x4[0x8]; int hit; u8 unknown_0x10[0x30]; union { u64 grf; struct { u32 grfLow; u32 grfHigh; }; }; };
extern "C" int FStgSwitchDone(STGSWITCH *);
extern "C" int FIsBasicDerivedFrom(void *, int);
extern "C" void SetStgSwitchHitter(STGSWITCH *, void *, int);
int func_001BADF0(STGSWITCH *stg, CONTACT *contact)
{
    if (FStgSwitchDone(stg))
        return 0;
    if (contact->grfHigh == 0)
        return 0;
    if ((contact->grf & 0xC00000000UL) != 0x800000000UL)
        return 1;
    if (stg->cclass != 0 && contact->toucher != stg) {
        int index = 0;
        while (index < stg->cclass) {
            if (FIsBasicDerivedFrom(contact->toucher, stg->aclass[index].cid))
                break;
            index++;
        }
        if (!(index < stg->cclass))
            return 0;
    }
    SetStgSwitchHitter(stg, contact->toucher, contact->hit);
    return 1;
}
