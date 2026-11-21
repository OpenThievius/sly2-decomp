#include "cref.h"

/* Reads a value of the game's save by a key built from a format and its arguments (other callers pass a format and names); the
   key here is "episodeBest" at 0x2A8A78. */
extern "C" {
CRef func_001D8A38(const char *pchzFormat, ...);
extern const char RO_002A8A78[];

s32 NEpisodeBest(void)
{
    return func_001D8A38(RO_002A8A78, 0).m_tag.m_n;
}
}
