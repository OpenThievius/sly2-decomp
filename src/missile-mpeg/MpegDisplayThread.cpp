#include "types.h"
#include "cmpeg.h"
struct LM;
struct sceDmaChan;
struct TIMES { u8 unknown_0x0[0x3C]; float tScreen; };
extern "C" void WaitSema(int);
extern "C" void SendDmaSyncGsFinish__FP10sceDmaChanP2QW(sceDmaChan *, void *);
extern "C" void RestoreGsBuffers__Fv();
extern "C" void SwapGsBuffers__Fv();
extern "C" int FCheckLm__FP2LMf(LM *, float);
extern "C" CMpeg B_002F66B0;
extern "C" sceDmaChan *g_2de598;
extern "C" TIMES g_2dded0;
void MpegDisplayThread()
{
    for (;;) {
        B_002F66B0.pending = 0;
        WaitSema(B_002F66B0.sema);
        void *ppacketSubtitle = 0;
        B_002F66B0.pending = 1;
        SendDmaSyncGsFinish__FP10sceDmaChanP2QW(g_2de598, B_002F66B0.pbBuffer + 0x3F8E80);
        B_002F66B0.pending = 2;
        RestoreGsBuffers__Fv();
        if (B_002F66B0.psubtitle != 0) {
            if (FCheckLm__FP2LMf((LM *)((char *)B_002F66B0.psubtitle + 8), g_2dded0.tScreen - B_002F66B0.tPicture))
                ppacketSubtitle = B_002F66B0.pbBuffer + 0x41DC00;
        }
        SendDmaSyncGsFinish__FP10sceDmaChanP2QW(g_2de598, B_002F66B0.pbBuffer + 0x41BC00);
        if (ppacketSubtitle != 0)
            SendDmaSyncGsFinish__FP10sceDmaChanP2QW(g_2de598, ppacketSubtitle);
        SwapGsBuffers__Fv();
        SendDmaSyncGsFinish__FP10sceDmaChanP2QW(g_2de598, B_002F66B0.pbBuffer + 0x41BC00);
        if (ppacketSubtitle != 0)
            SendDmaSyncGsFinish__FP10sceDmaChanP2QW(g_2de598, ppacketSubtitle);
        SwapGsBuffers__Fv();
    }
}
