#include "cref.h"
struct CProc { int cref; }; /* the reference count first, as Splice's other heap values */
extern "C" void CRef_Destruct(CRef *);

CRef *CRef_SetProc(CRef *pref, CProc *pproc) {
    pproc->cref += 1;
    CRef_Destruct(pref);
    pref->m_tag.m_pproc = pproc;
    pref->m_tagk = TAGK_Proc;
    return pref;
}
