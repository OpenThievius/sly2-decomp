#include "sly2.h"
struct TEX0 {
    u64 tbp0 : 14;
    u64 tbw : 6;
    u64 psm : 6;
    u64 tw : 4;
    u64 th : 4;
    u64 tcc : 1;
    u64 rest : 29;
};
struct BMP { u8 unknown_0x0[8]; u16 w; u16 h; u8 psm; u8 tbw; u8 unknown_0xE[0x12]; TEX0 tex0; };
extern "C" unsigned NLog2__FUi(unsigned);

void BuildBmpTex0__FP3BMPi(BMP *pbmp, int iblock)
{
    pbmp->tex0.tbp0 = iblock;
    pbmp->tex0.tbw = pbmp->tbw;
    pbmp->tex0.psm = pbmp->psm;
    pbmp->tex0.tw = NLog2__FUi(pbmp->w);
    pbmp->tex0.th = NLog2__FUi(pbmp->h);
    pbmp->tex0.tcc = 1;
}
