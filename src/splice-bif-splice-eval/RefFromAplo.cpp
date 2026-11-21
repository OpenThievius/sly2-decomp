// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
struct CPair { int pad0; int pad4; CRef ref; CPair *next; };
extern "C" {
void CRef_CopyConstruct(CRef *, CRef *);
void PairHandle_Assign(CPair **, CPair *);
CPair *PpairNew();
void bevy_splice_value_list_ref(CRef *, CPair *);
}
extern "C" CRef *RefFromAplo(CRef *pret, int cplo, int *aplo)
{
    if (cplo == 0) {
        pret->SetTag((TAGK)0);
        return pret;
    }
    CRef refList;
    refList.m_tagk = TAGK_Nil;
    CPair *pprev = 0;
    if (cplo > 0) {
        int *pplo = aplo;
        unsigned int index = cplo;
        do {
            CPair *ppair = PpairNew();
            if (pprev != 0) {
                PairHandle_Assign(&pprev->next, ppair);
            } else {
                bevy_splice_value_list_ref(&refList, ppair);
            }
            int plo = *pplo;
            ppair->ref.SetBasic((BASIC *)plo);
            pprev = ppair;
            pplo++;
            index--;
        } while (index != 0);
    }
    CRef_CopyConstruct(pret, &refList);
    return pret;
}
