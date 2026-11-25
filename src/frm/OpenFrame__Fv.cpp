#include "sly2.h"
#include "frm.h"
struct DMAS;
extern int B_003D3980;
extern int g_2deb1c;
extern unsigned B_002DEB10;
extern FRM B_002DEA50[2];
extern FRM *g_2dea4c;
extern int g_2ddf54;
extern char B_002DEA00[];
extern char g_2dea28[];
extern char B_002DF740[];
extern "C" void func_001C2A78(int);
extern "C" void WaitSema(int);
void ClearPendingFrame(FRM *);
void AllocStatic__4DMASiP2QW(void *, int, QW *);
void AddDmaRefs__4DMASiP2QW(void *, int, QW *);
void AddDmaCnt__4DMAS(void *);
void OpenFrame__Fv()
{
    if (B_003D3980 == 0) func_001C2A78(3);
    WaitSema(g_2deb1c);
    unsigned i = B_002DEB10;
    B_002DEB10 = i + 1;
    g_2dea4c = &B_002DEA50[i];
    if (B_002DEB10 >= 2) B_002DEB10 = 0;
    ClearPendingFrame(g_2dea4c);
    FRM *f = g_2dea4c;
    f->field_0x4C = g_2ddf54;
    f->grf = 1;
    f->grfFontLoaded = 0;
    f->pqwVifSend = 0;
    AllocStatic__4DMASiP2QW(B_002DEA00, f->cqwGifBuffer, f->pqwGifBuffer);
    AllocStatic__4DMASiP2QW(g_2dea28, g_2dea4c->cqwVifBuffer, g_2dea4c->pqwVifBuffer);
    AddDmaRefs__4DMASiP2QW(B_002DEA00, 12, (QW *)B_002DF740);
    AddDmaCnt__4DMAS(B_002DEA00);
}
