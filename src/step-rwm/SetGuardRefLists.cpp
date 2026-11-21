#include "cref.h"
extern "C" CRef func_002013D8(CRef *, int, int, int *, int *);

void SetGuardRefLists(char *guard, CRef *candidates, CRef *blockers)
{
    CRef holder;
    holder.m_tagk = TAGK_Nil;
    holder = func_002013D8(candidates, 0x2002, 4, (int *)(guard + 0xF94), (int *)(guard + 0xF98));
    holder = func_002013D8(blockers, 0x2002, 4, (int *)(guard + 0xFA8), (int *)(guard + 0xFAC));
}
