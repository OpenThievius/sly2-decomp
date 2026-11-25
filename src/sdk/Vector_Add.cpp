#include "cvector.h"
extern "C" void func_00116E30(CARY *, const void *, int);
extern "C" int *Vector_Add(CVECTOR *pvec, const void *pvSrc)
{
    CARY *pary = &pvec->ary;
    func_00116E30(pary, pvSrc, 1);
    pvec->OnAdd(&pvec->ary.pb[pary->c - 1]);
    return &pvec->ary.pb[pary->c - 1];
}
