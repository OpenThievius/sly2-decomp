#include "cref.h"
struct SAVEPATH { int csym; short *asym; };
extern "C" {
extern int B_003D4A60[];
void CStackFrame_Construct(void *);
void CStackFrame_Destructor(void *, int);
SAVEPATH *PpathVaultFlag(void);
CRef RefGetGameSaveValue(void *, int *);
}
static inline int GetSaveInt_1C8110(void *path)
{
    int n = RefGetGameSaveValue(path, B_003D4A60).m_tag.m_n;
    return n;
}
extern "C" int FVaultOpen(void)
{
    char frame[0x10];
    CStackFrame_Construct(frame);
    SAVEPATH *path = PpathVaultFlag();
    if (path == 0) {
        CStackFrame_Destructor(frame, 2);
        return 0;
    }
    int result = GetSaveInt_1C8110(path);
    CStackFrame_Destructor(frame, 2);
    return result;
}
