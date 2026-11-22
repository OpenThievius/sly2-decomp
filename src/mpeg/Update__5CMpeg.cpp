// SPDX-License-Identifier: GPL-3.0-or-later
#include "cmpeg.h"
extern "C" int CMpeg_CbDemuxed(CMpeg *, int);
extern "C" int sceMpegGetPicture(void *, void *, int);
extern "C" void BuildMpegGifs__FP2QWP11sceIpuRGB32iiiii(CMpeg *);
extern "C" void DrawMpegFrame(CMpeg *);
extern "C" void FlushCache(int);
extern "C" void SignalSema(int);
extern float g_2ddf0c;

void CMpeg::Update()
{
    int p;
    int q;
    if (pending == 1) {
        do {
            CMpeg_CbDemuxed(this, 0);
            p = pending;
        } while (p == 1);
    }
    int result = sceMpegGetPicture(sdk, pbBuffer + 0x285a80, 0x5cd);
    if (result >= 0) {
        if (skipDraw == 0) {
            tPicture = g_2ddf0c;
            BuildMpegGifs__FP2QWP11sceIpuRGB32iiiii(this);
            DrawMpegFrame(this);
            FlushCache(0);
        }
        if (pending != 0) {
            do {
                CMpeg_CbDemuxed(this, 0);
                q = pending;
                } while (q != 0);
        }
        SignalSema(sema);
        audio.Update();
    }
}
