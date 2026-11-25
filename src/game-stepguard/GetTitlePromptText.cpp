#include "cref.h"
struct JB { u8 unknown_0x0[0x100C]; int a; int b; };
struct SLOTHOLDER { u8 unknown_0x0[0x8000 + 0x7D54]; int pslot; };
#include "sw.h"
extern JB B_002DFC00;
extern SLOTHOLDER B_002E65E0;
extern SW B_003DD490;
extern "C" const char RO_002A7A70[];
extern "C" char *strcpy(char *, const char *);
extern "C" char *strcat(char *, const char *);
extern "C" CRef RefGetGameSaveValue(SAVEPATH *, int);
extern "C" int func_001A2C98();
const char *PchzStringFromId(void *, int);

extern "C" void GetTitlePromptText(char *pchz)
{
    if (B_002DFC00.a == 1 && B_002DFC00.b == 0) {
        strcpy(pchz, PchzStringFromId(&B_003DD490, 9));
        return;
    }
    float tPlayed = 0.0f;
    if (B_002E65E0.pslot != 0) {
        tPlayed = RefGetGameSaveValue(B_003DD490.psavepathDt, B_002E65E0.pslot).m_tag.m_g;
    }
    int sid = (tPlayed != 0.0f) ? 6 : 5;
    strcpy(pchz, PchzStringFromId(&B_003DD490, sid));
    strcat(pchz, RO_002A7A70);
    strcat(pchz, PchzStringFromId(&B_003DD490, 8));
    if (func_001A2C98() > 1) {
        strcat(pchz, RO_002A7A70);
        strcat(pchz, PchzStringFromId(&B_003DD490, 0x56));
    }
}
