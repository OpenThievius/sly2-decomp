struct CRef { int tagk; float g; int p2; int p3; };
#include "sw.h"
extern SW B_003DD490;
extern char B_002E6604[];
extern char B_003D9ED0[];
extern "C" const char RO_002A6EC8[];
extern "C" char *strcpy(char *, const char *);
extern "C" int sprintf(char *, const char *, ...);
extern "C" void CRef_Destruct(CRef *);
extern "C" void RefGetGameSaveValue(CRef *, SAVEPATH *, char *);
extern "C" void CStackFrame_Construct(void *);
extern "C" void CStackFrame_Destructor(void *, int);
extern "C" int NPercentCompleteSaveData(void *, char *);
extern "C" SAVEPATH *PsavepathNewStack(const char *, int);
extern "C" int SidEpisodeName(int);
extern "C" int func_001B0078(void *);
const char *PchzStringFromId(void *, int);

extern "C" void func_001ADC40(char *pchz, int islot)
{
    char *pslot = B_002E6604 + islot * 0x5464;
    SW *pswLater = &B_003DD490;
    CRef ref;
    RefGetGameSaveValue(&ref, B_003DD490.psavepathDt, pslot);
    float dt = ref.g;
    CRef_Destruct(&ref);
    float zero;
    zero = 0.0f;
    if (dt != zero) {
        char frame[16];
        CStackFrame_Construct(frame);
        SAVEPATH *ppath = PsavepathNewStack("episodeBest", 0);
        if (ppath == 0)
            ppath = B_003DD490.psavepathEpisodeCurrent;
        RefGetGameSaveValue(&ref, ppath, pslot);
        int nEpisode = *(int *)&ref.g;
        CRef_Destruct(&ref);
        const char *pchzEpisode = PchzStringFromId(pswLater, SidEpisodeName(nEpisode));
        sprintf(pchz, RO_002A6EC8, pchzEpisode, NPercentCompleteSaveData((char *)pswLater + 0x3A18, pslot));
        CStackFrame_Destructor(frame, 2);
        return;
    }
    int nMode = func_001B0078(B_003D9ED0);
    if (nMode != 0x19) {
        if (nMode >= 0x19) {
            if (nMode < 0x20) {
                if (nMode >= 0x1E)
                    strcpy(pchz, PchzStringFromId(&B_003DD490, 0x44));
            }
        }
    } else {
        strcpy(pchz, PchzStringFromId(&B_003DD490, 0x45));
    }
}
