#include "sly2.h"
#include "so.h"
struct RO { u8 unknown_0x0[8]; s32 count; };
extern char B_003E12D4[];
extern "C" void FreeSlotheapPv(char *, RO *);
extern "C" int FIsBasicDerivedFrom(LO *, int);
extern "C" void func_001F2468(SO *);

extern "C" void func_001F2468(SO *pso)
{
    RO *ref = pso->field_0x134;
    if (ref) {
        if (--ref->count == 0)
            FreeSlotheapPv(B_003E12D4, ref);
        pso->field_0x134 = 0;
    }
    for (LO *plo = (LO *)pso->dlChild.head; plo != pso->ploChildEnd; plo = plo->ploNext) {
        if (FIsBasicDerivedFrom(plo, 0x30))
            func_001F2468((SO *)plo);
    }
}
