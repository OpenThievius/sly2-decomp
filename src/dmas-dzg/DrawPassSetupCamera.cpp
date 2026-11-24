#include "sly2.h"
#include "sw.h"
#include "cm.h"
struct V3_157CF0 { char xy[8]; int z; };
struct V4_157CF0 { V3_157CF0 v; float w; };
/* the DMA stream a pass appends to (name from the mangled methods; only the word at 0x20 is read here) */
struct DMAS { u8 unknown_0x0[0x20]; s32 field_0x20; };
extern "C" {
void AddDmaCall__4DMASP2QW(void *, void *);
int AddDmaCnt__4DMAS(void *);
void AddVifBaseOffset__4VIFSii(void *, int, int);
void AddVifDirect__4VIFSiP2QWi(void *, int, void *, int);
int AddVifFlush__4VIFS(void *);
void AddVifUnpack__4VIFS3UPKiPvi(void *, int, int, void *, int);
void EndDmaCnt__4DMAS(void *);
void *bevy_camera_cm_14f768(void *, int, int, void *, void *);
void func_0016E1A8(void *, int, int);
extern char B_002DEA50[];
extern char B_002DF010[];
extern char B_002DF800[];
extern char B_002DF940[];
extern char B_002DFA80[];
extern SW B_003DD490;
extern QW B_003E12B8;
extern char D_002C1F00[];
extern char D_002C1F10[];
extern void *g_2dea4c;
void DrawPassSetupCamera(DMAS *arg0, int arg1, int arg2) {
    V4_157CF0 params[2];
    QW mat[8];
    if (B_003DD490.field_0x3E38 != 0) {
        if (g_2dea4c == (void *)B_002DEA50) {
            AddDmaCall__4DMASP2QW(arg0, B_002DF940);
        } else {
            AddDmaCall__4DMASP2QW(arg0, B_002DFA80);
        }
    } else {
        AddDmaCall__4DMASP2QW(arg0, B_002DF800);
    }
    arg0->field_0x20 = 1;
    AddDmaCnt__4DMAS(arg0);
    AddVifFlush__4VIFS(arg0);
    AddVifDirect__4VIFSiP2QWi(arg0, 0x25, B_002DF010, 0);
    AddVifBaseOffset__4VIFSii(arg0, 0, 0);
    params[0].v = *(V3_157CF0 *)D_002C1F00;
    float ratio = (B_002DDF40.sNearClip + B_002DDF40.sFarClip) / (B_002DDF40.sNearClip - B_002DDF40.sFarClip);
    float scale = B_002DDF40.sNearClip * (1.0f - ratio);
    params[0].w = 1.0f / scale;
    params[1].v = *(V3_157CF0 *)D_002C1F10;
    params[1].w = -ratio / scale;
    AddVifUnpack__4VIFS3UPKiPvi(arg0, 0xC, 2, params, 0);
    if (B_003DD490.field_0x3E38 != 0) {
        if (g_2dea4c == (void *)B_002DEA50) {
            bevy_camera_cm_14f768(&B_002DDF40, 1, 0, mat, mat + 4);
        } else {
            bevy_camera_cm_14f768(&B_002DDF40, 2, 0, mat, mat + 4);
        }
    } else {
        QW *proj = B_002DDF40.matClip.row;
        QW *view = B_002DDF40.mat.row;
        mat[0] = B_002DDF40.matClip.row[0];
        mat[1] = proj[1];
        mat[2] = proj[2];
        mat[3] = proj[3];
        mat[4] = B_002DDF40.mat.row[0];
        mat[5] = view[1];
        mat[6] = view[2];
        mat[7] = view[3];
    }
    AddVifUnpack__4VIFS3UPKiPvi(arg0, 0xC, 4, mat, 2);
    AddVifUnpack__4VIFS3UPKiPvi(arg0, 0xC, 4, mat + 4, 6);
    AddVifUnpack__4VIFS3UPKiPvi(arg0, 0xC, 1, &B_003E12B8, 0xA);
    AddVifBaseOffset__4VIFSii(arg0, 0x32, 0x1E7);
    EndDmaCnt__4DMAS(arg0);
    func_0016E1A8(arg0, arg1, arg2);
}
}
