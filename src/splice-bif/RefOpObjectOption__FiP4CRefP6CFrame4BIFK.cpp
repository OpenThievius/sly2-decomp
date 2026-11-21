#include "sly2.h"
#include "cref.h"
struct CFrame;
extern "C" void RefAddOption__FP5BASICiP4CRef(CRef *, int, int, CRef *);
extern "C" void RefEnsureOption__FP5BASICiP4CRef(CRef *, int, int, CRef *);
extern "C" void RefSetOption__FP5BASICiP4CRef(CRef *, int, int, CRef *);
extern "C" void RefGetOption(CRef *, int, int);

extern "C" CRef RefOpObjectOption__FiP4CRefP6CFrame4BIFK(int carg, CRef *aref, CFrame *pframe, int bifk)
{
    int pbasic = aref[0].m_tag.m_n;
    int oid = aref[1].m_tag.m_n;
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    switch (bifk) {
    case 0x6c: {
        CRef refOption;
        RefAddOption__FP5BASICiP4CRef(&refOption, pbasic, oid, &aref[2]);
        refResult = refOption;
        break;
    }
    case 0x6d: {
        CRef refOption;
        RefEnsureOption__FP5BASICiP4CRef(&refOption, pbasic, oid, &aref[2]);
        refResult = refOption;
        break;
    }
    case 0x6e: {
        CRef refOption;
        RefSetOption__FP5BASICiP4CRef(&refOption, pbasic, oid, &aref[2]);
        refResult = refOption;
        break;
    }
    case 0x6f: {
        CRef refOption;
        RefGetOption(&refOption, pbasic, oid);
        refResult = refOption;
        break;
    }
    }
    return refResult;
}
