#include "goal.h"
/* a command of a script (script.h PCMD): the link to the next one is at 0x18 */
struct PCMDNODE {
    u8 unknown_0x0[0x18];
    PCMDNODE *next;
};
/* a guard's script behaviour (a GOAL, GUARDSCRIPTBEH of guardscriptbeh.h with its virtuals): pcmd is the current command */
struct GUARDSCRIPTBEHV : GOAL {
    u8 unknown_0x30[0x38 - 0x30];
    /* 0x38 */ PCMDNODE *pcmd;
    virtual void ExecuteCmd(PCMDNODE *pcmd); /* 15 */
};
extern "C" {
int FGuardScriptWaiting(GUARDSCRIPTBEHV *);
void func_001EEF98();
void UpdateGuardScriptBeh(GUARDSCRIPTBEHV *self) {
    func_001EEF98();
    if (self->pcmd != 0) {
        do {
            if (FGuardScriptWaiting(self) != 0)
                break;
            PCMDNODE *next = self->pcmd->next;
            self->pcmd = next;
            if (next == 0)
                break;
            self->ExecuteCmd(next);
        } while (self->pcmd != 0);
    }
}
}
