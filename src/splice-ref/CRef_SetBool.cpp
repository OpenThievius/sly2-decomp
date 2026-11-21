#include "sly2.h"
#include "cref.h"

CRef &CRef::SetBool(int fBool)
{
    Decref();
    m_tag.m_bool = fBool;
    m_tagk = TAGK_Bool;
    return *this;
}
