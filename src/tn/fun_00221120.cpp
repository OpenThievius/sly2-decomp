#include "tn.h"
int func_00221120(TN *tn, void **out)
{
    if (!tn->pcrv) return 0;
    *out = &tn->pcrv;
    return 1;
}
