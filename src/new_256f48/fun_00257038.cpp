#include "types.h"
struct REFCOUNTED {
    s32 cRef; /* reader: func_00257038 (incremented when a reference is taken) */
};
void func_00257038(REFCOUNTED **ppDestination, REFCOUNTED *pSource)
{
    if (pSource != 0)
    {
        pSource->cRef = pSource->cRef + 1;
    }
    *ppDestination = pSource;
}
