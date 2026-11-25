// 0x120990 RefOpIsNull
#include "cref.h"
// retail writes the result through the hidden return pointer (no copy constructor call), so the result is an argument
extern "C" CRef *func_00120990(CRef *result, int carg, CRef *aref) {
    u32 tagk = aref[0].m_tagk;
    result->m_tagk = TAGK_Bool;
    result->m_tag.m_bool = tagk < 1u;
    return result;
}
