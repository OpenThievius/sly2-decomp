#include "cref.h"
struct ENT { int id; int unk; };
struct SHOPMENU { char pad0[0x4C]; ENT aent[0x40]; char padx[0x250 - 0x4C - 0x40 * 8]; int ifirst; };
struct LOOT { int a; int sidName; int c; };
extern SHOPMENU B_003DA150;
extern char B_003DD490;
extern LOOT D_002C3288[];
extern "C" const char RO_002A79A0[];
extern "C" const char RO_002A79D0[];
extern "C" const char RO_002A79D8[];
extern "C" const char RO_002A7A30[];
extern "C" int sprintf(char *, const char *, ...);
extern "C" char *strcpy(char *, const char *);
extern "C" CRef func_001D8A38(const char *, const char *, const char *, int);
const char *PchzStringFromId(void *, int);

void GetLootRowName(char *pchz, int irow)
{
    int sid = -1;
    int cloot = 0;
    unsigned loot = B_003DA150.aent[B_003DA150.ifirst + irow].id;
    if (loot < 0x40) {
        CRef ref;
        ref.m_tagk = TAGK_Nil;
        char achzIndex[0x20];
        sprintf(achzIndex, RO_002A79A0, loot);
        ref = func_001D8A38(RO_002A79D0, RO_002A79D8, achzIndex, 0);
        sid = D_002C3288[loot].sidName;
        cloot = ref.m_tag.m_n;
    }
    if (sid != -1) {
        strcpy(pchz, PchzStringFromId(&B_003DD490, sid));
        if (1 < cloot)
            sprintf(pchz, RO_002A7A30, pchz, cloot);
    } else {
        pchz[0] = 0;
    }
}
