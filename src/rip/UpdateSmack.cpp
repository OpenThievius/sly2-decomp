#include "rip.h"
extern "C" float g_2dded0;
extern "C" void RemoveRip(void *);

struct B8 { char b[8]; };
struct OBJ { virtual void v0(); int pad; };
typedef void (OBJ::*PMF)(void *);

struct SMI { u8 unknown_0x0[0x60]; B8 pmf; };
struct SMACK : RIP {
    SMI *info;
    OBJ *target;
    void *arg;
};

void UpdateSmack(SMACK *smack, float dt)
{
    if (smack->dtLifetime < g_2dded0 - smack->tStart) {
        PMF pmf;
        *(B8 *)&pmf = smack->info->pmf;
        (smack->target->*pmf)(smack->arg);
        RemoveRip(smack);
    }
}
