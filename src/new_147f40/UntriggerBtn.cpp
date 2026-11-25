#include "button.h"
extern "C" {
void RunBtnAsegs(BTN *, int);
void UntriggerBtn(BTN *pbtn) {
    pbtn->pbutton->HandleSpliceEvent(6, 0, 0, 0, 0);
    RunBtnAsegs(pbtn, 1);
    pbtn->pbutton->PostMessage(7, pbtn);
}
}
