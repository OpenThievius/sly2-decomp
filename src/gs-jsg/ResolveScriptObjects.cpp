#include "sly2.h"
#include "script.h"
/* a command with its list link (InitScript's InitSl ibSle 0x18; ResolveScriptObjects walks it): script.h's PCMD, then the arguments */
struct PCMDNODE {
    PCMD pcmd;
    u8 unknown_0x8[0x10];
    /* 0x18 */ PCMDNODE *pcmdNext;
};
extern char B_003DD490[];
extern "C" void *PloFindSwObject_thunk(void *, int, int, void *);
extern "C" int func_001709A8(void *);
extern "C" void EnsureCrvExcludedRanges(void *);
extern "C" void ResolveScriptObjects(SCRIPT *pscript)
{
    void *ploContext = pscript;
    PCMDNODE *pcmd = (PCMDNODE *)pscript->slPcmd.pvFirst;
    while (pcmd != 0) {
        if (pcmd->pcmd.type != 0) {
            if (pcmd->pcmd.type == 6) {
                void *plo = PloFindSwObject_thunk(B_003DD490, 4, pcmd->pcmd.oid, ploContext);
                if (plo != 0 && func_001709A8(plo) == -1)
                    EnsureCrvExcludedRanges(plo);
            }
        } else {
            ploContext = PloFindSwObject_thunk(B_003DD490, ploContext != 0 ? 4 : 5, pcmd->pcmd.oid, ploContext);
        }
        pcmd = pcmd->pcmdNext;
    }
}
