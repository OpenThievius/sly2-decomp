#include "button.h"
extern "C" {
void TriggerBtn(BTN *);
void UntriggerBtn(BTN *);
extern float g_2dded0;
void SetBtnButtons__FP3BTN7BUTTONS(BTN *self, int buttons) {
    int old = self->buttons;
    if (old != buttons) {
        int trigger = (old == 0) && (buttons == 1);
        int untrigger = (old != -1) && (buttons == 0);
        *(int *)((char *)self + 0x90) = buttons;
        self->tButtons = g_2dded0;
        if (trigger) TriggerBtn(self);
        if (untrigger) UntriggerBtn(self);
    }
}
}
