#include "oxa.h"
#include "so.h"
extern "C" int GetSoNoXpsAll(SO *so)
{
    if (so->poxa == 0)
        return 1;
    return (int)(so->poxa->grf >> 2) & 1;
}
