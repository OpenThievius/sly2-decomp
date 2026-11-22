// SPDX-License-Identifier: GPL-3.0-or-later
#include "bentley.h"
extern "C" void RetractSmaRef(void *);
extern "C" void ApplyAsegToHandle(void *, void *, int, void *, float, float);

/* the three words of STEP::velGoal that the first gadget state clears (its w lane stays) */
struct V3 { int x, y, z; };

/* the gadget animations SetBentleyGadgetAnim picks: a view of BENTLEY (one reader each; not a method of the class) */
struct BENTLEYGADGETANIMS {
    u8 unknown_0x0[0x14E4];
    /* 0x14E4 */ ASEG *field_0x14E4; /* gadget state 0 */
    /* 0x14E8 */ ASEG *field_0x14E8; /* gadget state 2, when set */
    u8 unknown_0x14EC[0xE8];
    /* 0x15D4 */ ASEG *field_0x15D4; /* gadget state 2 when field_0x14E8 is 0 */
    u8 unknown_0x15D8[0x18];
    /* 0x15F0 */ ASEG *field_0x15F0; /* gadget state 1 */
};

void SetBentleyGadgetAnim(BENTLEY *pbentley, int gadgets)
{
    if (gadgets == pbentley->field_0x16B0) return;
    pbentley->field_0x16B0 = gadgets;
    void *paseg = 0;
    int grfapl = 1;
    switch (gadgets) {
    case 0:
        paseg = ((BENTLEYGADGETANIMS *)pbentley)->field_0x14E4;
        { V3 *v = (V3 *)&pbentley->velGoal; v->z = 0; v->y = 0; v->x = 0; }
        break;
    case 1:
        paseg = ((BENTLEYGADGETANIMS *)pbentley)->field_0x15F0;
        grfapl = 9;
        break;
    case 2:
        paseg = ((BENTLEYGADGETANIMS *)pbentley)->field_0x14E8;
        if (paseg == 0) paseg = ((BENTLEYGADGETANIMS *)pbentley)->field_0x15D4;
        grfapl = 9;
        break;
    }
    RetractSmaRef(&pbentley->field_0x1034);
    ApplyAsegToHandle(paseg, pbentley, grfapl, &pbentley->field_0x1030, 0.0f, 1.0f);
    pbentley->Slot90();
}
