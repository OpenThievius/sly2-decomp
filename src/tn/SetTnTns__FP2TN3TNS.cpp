// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "tn.h"
#include "so.h"
#include "cm.h"
#include "clock.h"
enum CPP { CPP_NONE = -1, CPP_DEFAULT = 1 };
/* B_002DDF40's tunnel policy: SetTnTns passes the CPLCY at 0x3B0 of the camera manager */
struct CMTN {
    u8 unknown_0x0[0x3B0];
    CPLCY cplcyTn;
};
void SetCmPolicy(CM *, CPP, CPLCY *, SO *, void *);
void RevokeCmPolicy(CM *, int, CPP, CPLCY *, SO *, void *);

void SetTnTns(TN *tn, TNS tns)
{
    if (tns == tn->tns)
        return;
    switch (tns) {
    case TNS_ON:
        SetCmPolicy(&B_002DDF40, (CPP)(tn->pri + 2), &((CMTN *)&B_002DDF40)->cplcyTn, tn->psoFocus, tn);
        tn->HandleSpliceEvent(5, 1, 0, 0, 0);
        tn->tns = tns;
        break;
    case TNS_OFF:
        RevokeCmPolicy(&B_002DDF40, 8, CPP_NONE, 0, 0, tn);
        tn->HandleSpliceEvent(6, 1, 0, 0, 0);
    default:
        tn->tns = tns;
        break;
    }
    tn->tTns = g_2dded0.t;
}
