// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
struct SAVEPATH { char b[0x10]; };
struct CFrame;
extern "C" char B_003E0EA8[];
extern "C" char B_003D4A60[];
extern "C" void CStackFrame_Construct(void *);
extern "C" void CStackFrame_Destructor(void *, int);
extern "C" void ConvertListToSavePath(int, SAVEPATH *);
extern "C" CRef RefGetSaveValue(void *, SAVEPATH *, void *);
struct CStackFrame {
    char b[0x10];
    CStackFrame() asm("CStackFrame_Construct");
    ~CStackFrame() { CStackFrame_Destructor(this, 2); }
};

extern "C" CRef bevy_audio_bif_stop_sound(int carg, CRef *aref, CFrame *pframe)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    CStackFrame frame;
    SAVEPATH path;
    ConvertListToSavePath(aref[0].m_tag.m_n, &path);
    refResult = RefGetSaveValue(B_003E0EA8, &path, B_003D4A60);
    return refResult;
}
