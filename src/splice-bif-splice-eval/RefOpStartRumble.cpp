#include "sly2.h"
#include "cref.h"
struct JOY;
extern JOY B_002DFC00;
extern "C" CRef CRef_RefCoerceF32(CRef *);
extern "C" void TriggerJoyRumbleRumk__FP3JOY4RUMKf(JOY *, int, float);

CRef RefOpStartRumble(int count, CRef *args, void *frame)
{
    JOY *pjoy = &B_002DFC00;
    int rumk = args[0].m_tag.m_n;
    {
        CRef refTemp = CRef_RefCoerceF32(args + 1);
        TriggerJoyRumbleRumk__FP3JOY4RUMKf(pjoy, rumk, refTemp.m_tag.m_g);
    }
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    return refResult;
}
