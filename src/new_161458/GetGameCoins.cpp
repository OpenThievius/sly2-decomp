#include "cref.h"
extern "C" {
CRef RefGetGameSaveValue(int, void *);
extern char B_003D4A60[];
extern int B_003E0FB0;
}
extern "C" s32 GetGameCoins(void)
{
    return RefGetGameSaveValue(B_003E0FB0, B_003D4A60).m_tag.m_n;
}
