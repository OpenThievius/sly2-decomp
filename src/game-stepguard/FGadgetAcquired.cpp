#include "sly2.h"
#include "cref.h"
extern char RO_002A79A0[], RO_002A79A8[], RO_002A79B8[];
extern "C" {
int sprintf(char *, const char *, ...);
CRef func_001D8A38(const char *, ...);
}
int FGadgetAcquired(int gadget)
{
    if (gadget == -1)
        return 0;
    CRef ref;
    ref.m_tagk = TAGK_Nil;
    char idx[0x20];
    sprintf(idx, RO_002A79A0, gadget);
    ref = func_001D8A38(RO_002A79A8, RO_002A79B8, idx, 0);
    int on = ref.m_tag.m_n;
    return on;
}
