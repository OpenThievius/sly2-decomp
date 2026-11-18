#include "sly2.h"
struct CRef { int tagk; float g; int p2; int p3; };
#include "sw.h"
struct SS { char pad[0x24]; int icur; };
struct E { char pad[0x14]; int slot; char pad2[4]; };
extern SW B_003DD490;
extern SS B_003D9ED0;
extern E B_003D9EDC[];
extern char B_002E6604[];
extern "C" const char RO_STR_002A6ED8[];
extern "C" {
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
void CRef_Destruct(CRef *);
void RefGetGameSaveValue(CRef *, void *, void *);
int func_001B0108(void *);
int func_001B0078(void *);
}
const char *PchzStringFromId(void *, int);

void func_001ADA20(char *pchz)
{
    SS *pss = &B_003D9ED0;
    if (func_001B0108(pss) == 0) return;
    CRef refDt;
    SW *psw = &B_003DD490;
    RefGetGameSaveValue(&refDt, psw->psavepathDt, B_002E6604 + B_003D9EDC[pss->icur].slot * 0x5464);
    float dt = refDt.g;
    CRef_Destruct(&refDt);
    switch (func_001B0078(pss)) {
    case 0x1E:
        if (dt == 0.0f) goto zero;
        strcpy(pchz, PchzStringFromId(psw, 0x25));
        break;
    case 0x1F:
        if (dt == 0.0f) goto zero;
        strcpy(pchz, PchzStringFromId(psw, 0x27));
        break;
    zero:
        strcpy(pchz, PchzStringFromId(psw, 0x26));
        break;
    case 0x19:
        strcpy(pchz, PchzStringFromId(psw, 0x29));
        if (dt != 0.0f) {
            strcat(pchz, RO_STR_002A6ED8);
            strcat(pchz, PchzStringFromId(psw, 0x25));
        }
        break;
    }
}
