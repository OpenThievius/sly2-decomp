#include "alloc.h"
#include "bis.h"
#include "shd.h"
#include "shdframes.h"
#include "sl.h"
extern "C" {
void func_001EAE40(CBinaryInputStream *);
void LoadBitmapsFromBrx(CBinaryInputStream *);
int func_001ED7A8(int, CBinaryInputStream *);
void LoadShdFromBrx(CBinaryInputStream *, SHD *);
void func_0020F640(void *, CBinaryInputStream *);
void *PqwVifsBitmapUpload__Fi(void *, int);
void FillShaders__Fi();
void func_001EB678(SHD *, SHDFRAMES *);
void AppendSlEntry(SL *, void *);
void *PvAllocStackClearImpl__Fi(ALLOCREQ *);
void *PvAllocSwClearImpl__Fi(ALLOCREQ *);
}
extern int B_003DD000;
extern int *B_003DD004;
extern int B_003DCFE8;
extern SHD *B_003DCFEC;
extern unsigned int B_003DCFA0;
extern void *B_003DCFA8[];
extern SL B_003E1590;
void LoadShadersFromBrx(void *arg0, void *arg1, CBinaryInputStream *pbis) {
    ALLOCREQ request;
    func_001EAE40(pbis);
    LoadBitmapsFromBrx(pbis);
    B_003DD000 = pbis->U16Read();
    request.cb = B_003DD000 * 4;
    request.cbAlign = 0x10;
    B_003DD004 = (int *)PvAllocStackClearImpl__Fi(&request);
    for (int index = 0; index < B_003DD000; index++) {
        B_003DD004[index] = func_001ED7A8(0, pbis);
    }
    B_003DCFE8 = pbis->U16Read();
    request.cb = B_003DCFE8 * 0x2C;
    request.cbAlign = 0x10;
    B_003DCFEC = (SHD *)PvAllocStackClearImpl__Fi(&request);
    for (int index = 0; index < B_003DCFE8; index++) {
        LoadShdFromBrx(pbis, &B_003DCFEC[index]);
    }
    func_0020F640(arg0, pbis);
    void *upload = PqwVifsBitmapUpload__Fi(arg1, 3);
    if (upload != 0 && B_003DCFA0 < 0x10) {
        B_003DCFA8[B_003DCFA0++] = upload;
    }
    FillShaders__Fi();
    for (int index = 0; index < B_003DCFE8; index++) {
        SHD *shader = &B_003DCFEC[index];
        if (shader->grf & 0x40) {
            request.cb = 0x1C;
            request.cbAlign = 0x10;
            SHDFRAMES *entry = (SHDFRAMES *)PvAllocSwClearImpl__Fi(&request);
            func_001EB678(shader, entry);
            AppendSlEntry(&B_003E1590, entry);
        }
    }
}
