#include "sly2.h"
#include "sw.h"
#include "button.h"
/* an entry of a button's ASHLIST (button.h) once loaded: the animation segment record and its flags */
struct ASEGLOADED;
struct ASEGRECLOADED {
    LO *plo;
};
struct ASEGLOADED {
    u8 unknown_0x0[0x14];
    ASEGRECLOADED *rec;
};
struct ASHENTRYRUN {
    ASEGLOADED *paseg;
    int grfapl;
};
struct ASHLISTRUN {
    int caseg;
    ASHENTRYRUN aaseg[8];
};
/* the head of the BTN as this function walks it: the owner, then the two segment lists */
struct BTNRUN {
    BUTTON *pbutton;
    ASHLISTRUN aash[2];
};
enum SEEK { SEEK_X };
extern char B_002DEB30[];
extern "C" {
extern SW B_003DD490;
void *PloFindSwObject_thunk(void *, int, int, void *);
void PasegaEnsureAseg__FP4ASEGP3ALO4SEEKffi(ASEGLOADED *, void *, SEEK, float, float, int);
void TriggerRsmg(void *, int, void *, void *, int);
void StartJsg(void *, LO *);
void ApplyTaskStateRequests(void *, int, void *, void *);
}
// Retail: StartJsg takes (JSG *, ALO *): $a0 = pbtn->pjsg (0xAC), $a1 = pbtn->pjsgSubject (0xA8), so the
// call passes the joint-sequence pointer, not pbtn. The owner is read through pbtn->pbutton at each use (no
// copy into a local target first): retail keeps pbtn in $s0 and paseg in $s1, which a separate owner local
// swapped. An ASHLIST is exactly 0x44 bytes (count + 8 entries), no padding.
// Remaining (score 3): retail forms the loop entry pointer as iash*0x44 + (pbtn + 0xC); ours as
// (iash*0x44 + 0xC) + pbtn (loop.c giv base order). Entry-pointer, Ash-pointer, pointer-increment,
// unsigned iash, continue and statement-order (permuter) forms did not change it.
extern "C" void RunBtnAsegs(BTN *pbtn, int iash)
{
    int i;
    BTNRUN *view = (BTNRUN *)pbtn;
    for (i = 0; i < view->aash[iash].caseg; i++) {
        ASEGLOADED *paseg = view->aash[iash].aaseg[i].paseg;
        if (paseg != 0) {
            int oid = paseg->rec->plo->oid;
            int grf = view->aash[iash].aaseg[i].grfapl;
            void *target;
            if (pbtn->pbutton->oid == oid)
                target = pbtn->pbutton;
            else if (oid != -1)
                target = PloFindSwObject_thunk(&B_003DD490, 4, oid, pbtn->pbutton);
            else
                target = 0;
            if (pbtn->fSeekEnd != 0) {
                int seek = 0;
                if (pbtn->field_0x8C < 0.0f)
                    seek = 2;
                PasegaEnsureAseg__FP4ASEGP3ALO4SEEKffi(paseg, target, (SEEK)seek, 0.0f, pbtn->field_0x8C, grf);
            } else {
                PasegaEnsureAseg__FP4ASEGP3ALO4SEEKffi(paseg, target, (SEEK)1, 0.0f, pbtn->field_0x8C, grf);
            }
        }
    }
    TriggerRsmg(&B_003DD490, pbtn->crsmg, pbtn->arsmg, pbtn->pbutton, iash == 0);
    if (iash == 0) {
        if (pbtn->pjsg != 0)
            StartJsg(pbtn->pjsg, pbtn->pjsgSubject);
        ApplyTaskStateRequests(B_002DEB30, pbtn->ctaskreq, pbtn->ataskreq, pbtn->pbutton);
    }
}
