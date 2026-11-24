// 0x148718 InitBtn
#include "sly2.h"
#include "button.h"
void InitBtn(BTN* pbtn)
{
    pbtn->buttons = -1;
    pbtn->field_0x8C = 1.0f;
    pbtn->dtRepush = 1.0f;
}
