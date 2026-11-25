#include "sly2.h"
struct TEX0 {
    u64 tbp0 : 14;
    u64 tbw : 6;
    u64 psm : 6;
    u64 tw : 4;
    u64 th : 4;
    u64 tcc : 1;
    u64 tfx : 2;
    u64 cbp : 14;
    u64 cpsm : 4;
    u64 csm : 1;
    u64 csa : 5;
    u64 cld : 3;
};
struct CLUT { u8 unknown_0x0[8]; u16 count; u8 unknown_0xA[0xE]; TEX0 tex0; };

void BuildClutTex2__FP4CLUTi(CLUT *pclut, int iblock)
{
    pclut->tex0.cbp = iblock;
    pclut->tex0.psm = pclut->count <= 0x10 ? 0x14 : 0x13;
    pclut->tex0.cpsm = 0;
    pclut->tex0.csm = 0;
    pclut->tex0.csa = 0;
    pclut->tex0.cld = 1;
}
