#include "goal.h"
struct SCRIPTSTATE { int pcmd; int context; };
/* the script object: an LO (0x50 bytes) whose command list starts at 0x50 (script.h's SCRIPT) */
struct SCRIPT : LO {
    /* 0x50 */ int first;
};
/* a guard's script behaviour (a GOAL, GUARDSCRIPTBEH of guardscriptbeh.h with its virtuals) */
struct BEH : GOAL {
    /* 0x30 */ SCRIPT *script;
    /* 0x34 */ int context;
    /* 0x38 */ int cmd;
    u8 unknown_0x3C[4];
    /* 0x40 */ int unk40;
    /* 0x44 */ SCRIPTSTATE *state;
    u8 unknown_0x48[4];
    /* 0x4C */ int flag;
    virtual void ExecuteCmd(int cmd); /* 15 */
};
extern "C" void Goal_Pop(void *);
extern "C" void CFramePtr_Assign(void *, int);
extern "C" void SidebagPtr_Assign(void *, int);
extern "C" void SetGuardScript(BEH *beh, SCRIPT *script, int flag, SCRIPTSTATE *resume)
{
    if (script == beh->script)
        return;
    if (beh->script != 0) {
        Goal_Pop(&beh->pgoalChild);
        beh->HandleSpliceEvent(3, 0, 0, 0, 0);
        CFramePtr_Assign(&beh->pframe, 0);
        SidebagPtr_Assign(&beh->psidebag, 0);
        beh->context = 0;
        beh->cmd = 0;
        beh->unk40 = 0;
        beh->flag = 0;
    }
    beh->script = script;
    if (script == 0)
        return;
    CFramePtr_Assign(&beh->pframe, (int)script->pframe);
    beh->HandleSpliceEvent(2, 0, 0, 0, 0);
    beh->flag = flag;
    if (resume == 0 || resume->pcmd == 0) {
        SCRIPT *current = beh->script;
        int first = current->first;
        beh->context = (sptr)current;
        beh->cmd = first;
    } else {
        beh->cmd = resume->pcmd;
        beh->state = resume;
        beh->context = resume->context;
    }
    if (beh->cmd != 0)
        beh->ExecuteCmd(beh->cmd);
    beh->state = 0;
}
