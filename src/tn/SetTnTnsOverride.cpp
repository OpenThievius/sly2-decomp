#include "tn.h"
extern "C" void UpdateTnCallback(TN *, int);
void SetTnTnsOverride(TN *tn, int value)
{
    if (value != tn->tnsOverride) {
        tn->tnsOverride = value;
        UpdateTnCallback(tn, 0);
    }
}
