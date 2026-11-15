#include "cref.h"
extern int B_003D4A60;
extern int B_003E1BF4;
extern "C" void CStackFrame_Construct(void *);
extern "C" void CStackFrame_Destructor(void *, int);
extern "C" void *PpathClueFlag(int);
extern "C" int CcluesFound(void);
extern "C" CRef RefSetGameSaveValue(void *, const CRef &, int *);

static inline void SetSaveBool(void *path, int fBool, int *psave)
{
    CRef value;
    value.m_tagk = TAGK_Bool;
    value.m_tag.m_bool = fBool != 0;
    CRef copy(value);
    RefSetGameSaveValue(path, copy, psave);
}

void SetClueFound(int idClue, int fFound)
{
    char frame[16];
    CStackFrame_Construct(frame);
    void *path = PpathClueFlag(idClue);
    if (path == 0) {
        CStackFrame_Destructor(frame, 2);
        return;
    }
    SetSaveBool(path, fFound, &B_003D4A60);
    B_003E1BF4 = CcluesFound();
    CStackFrame_Destructor(frame, 2);
}
