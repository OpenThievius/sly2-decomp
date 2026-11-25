#include "sly2.h"
#include "joy.h"
#include "clock.h"
struct CODE { int *pgrf; int cgrf; u8 unknown_0x8[8]; int igrf; int unk14; CODE *pnext; };
struct CODELIST { CODE *pfirst; u8 unknown_0x4[0xC - 4]; float tFire; };
extern JOY B_002DFC00;
extern int B_003DA0B8;
void _MatchCodes__FP3JOYUs(CODELIST *plist, JOY *pjoy, unsigned short btn)
{
    if (pjoy != &B_002DFC00)
        return;
    if (btn == pjoy->grfbtnLatest || pjoy->grfbtnLatest == 0 || B_003DA0B8 == 0)
        return;
    for (CODE *pcode = plist->pfirst; pcode != 0; pcode = pcode->pnext) {
        int igrf = pcode->igrf;
        int fDone = igrf >= pcode->cgrf;
        if (!fDone) {
            if (pcode->pgrf[igrf] == pjoy->grfbtnLatest) pcode->igrf = igrf + 1; else pcode->igrf = 0;
        }
    }
    plist->tFire = g_2dded0.tReal + 1.0f;
}
