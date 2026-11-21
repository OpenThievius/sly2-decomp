#include "sly2.h"
#include "cref.h"

CRef &CRef::SetS32(int n)
{
    Decref();
    m_tag.m_n = n;
    m_tagk = TAGK_S32;
    return *this;
}
