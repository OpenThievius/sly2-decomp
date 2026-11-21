#include "sly2.h"
#include "cref.h"
struct CFrame;
extern "C" CRef RefCmp(CRef *, int);
CRef RefOpGE__FiP4CRefP6CFrame(int cref, CRef *aref, CFrame *pframe)
{
    return RefCmp(aref, 3);
}
