#include "sly2.h"
#include "cref.h"
struct CPair { int pad0; int pad4; CRef ref; CPair *unk0x10; };
struct CFrame;

CRef RefOpNth(int carg, CRef *aref, CFrame *pframe)
{
    CRef refResult;
    refResult.SetTag((TAGK)0);
    if (aref[0].m_tagk == 0x1F) {
        CRef *pnth = &aref[1];
        int index = 0;
        CPair *ppair = (CPair *)aref[0].m_tag.m_n;
        while (ppair != 0) {
            if (index == pnth->m_tag.m_n) {
                refResult = ppair->ref;
                break;
            }
            index++;
            ppair = ppair->unk0x10;
        }
    }
    return refResult;
}
