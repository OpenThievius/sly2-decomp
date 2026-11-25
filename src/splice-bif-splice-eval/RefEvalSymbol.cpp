#include "cref.h"
struct CFrame;
struct SYMBOLNODE { u8 unknown_0x0[0xC]; unsigned symid; }; /* a parsed symbol: its id at 0xC (reader: RefEvalSymbol) */
extern "C" void FFindBinding__6CFrameUiiP4CRef(CFrame *, unsigned int, int, CRef *);

extern "C" CRef RefEvalSymbol(SYMBOLNODE *psym, CFrame *pframe) {
    CRef ref;

    ref.m_tagk = TAGK_Nil;
    FFindBinding__6CFrameUiiP4CRef(pframe, psym->symid, 1, &ref);
    return ref;
}
