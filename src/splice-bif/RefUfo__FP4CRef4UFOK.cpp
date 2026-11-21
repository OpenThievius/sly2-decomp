#include "sly2.h"
#include "cref.h"
extern "C" void CRef_SetF32(CRef *, float);
enum UFOK { kUfokSqrt };
extern float (*D_002BBB70[])(float);

CRef RefUfo__FP4CRef4UFOK(CRef *ref, UFOK ufok)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    float value;
    if (ref->m_tagk == TAGK_F32) {
        value = ref->m_tag.m_g;
    } else {
        value = (float)ref->m_tag.m_n;
    }
    CRef_SetF32(&refResult, D_002BBB70[ufok](value));
    return refResult;
}
