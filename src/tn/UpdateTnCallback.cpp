#include "sly2.h"
#include "tn.h"
#include "po.h"
#include "jt.h"
#include "sw.h"

struct CGT;

extern SW B_003DD490;
extern int B_002DE240;
extern "C" PO *PpoSwFocus(void *);
extern "C" QW PosLoWorld(void *);
extern "C" QW ConvertAloPos(void *, void *, QW);
extern "C" CGT *PcgtPointInCbspQuick__FP4CBSPP6VECTOR(void *, int, QW);
extern "C" int FIsBasicDerivedFrom(void *, int);
extern "C" void SetTnTns__FP2TN3TNS(TN *, int);

// Retail loads tnsOverride once, copies it into the saved state register in the
// branch's delay slot and builds -1 afresh for the later field2DC and tnsOverride
// tests instead of keeping the first -1 in a fourth saved register. An if/else
// that tests the override first (`!= -1`) and assigns the state in each arm gives
// exactly that: the constant is not carried across the calls of the else arm.
void UpdateTnCallback(TN *tunnel)
{
    PO *focus = PpoSwFocus(&B_003DD490);
    if (focus == 0)
        return;
    if (focus != tunnel->psoFocus) {
        SetTnTns__FP2TN3TNS(tunnel, 0);
        tunnel->psoFocus = focus;
    }
    int tns;
    if (tunnel->tnsOverride != -1) {
        tns = tunnel->tnsOverride;
    } else {
        QW world = PosLoWorld(focus);
        QW local = ConvertAloPos(0, tunnel, world);
        tns = PcgtPointInCbspQuick__FP4CBSPP6VECTOR(tunnel->pcbsp, 0x7FFFFFFF, local) != 0;
    }
    if (tunnel->fAir != 0 || !FIsBasicDerivedFrom(focus, 0x34) || ((JT *)focus)->jmpState == -1 || B_002DE240 != 0
        || tunnel->tnsOverride != -1)
        SetTnTns__FP2TN3TNS(tunnel, tns);
}
