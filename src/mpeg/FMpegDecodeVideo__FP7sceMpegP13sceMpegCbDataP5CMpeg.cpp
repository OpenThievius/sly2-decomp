// SPDX-License-Identifier: GPL-3.0-or-later
#include "cmpeg.h"
extern "C" int CMpeg_CbDemuxed(CMpeg *, int);
extern "C" void *memset(void *, int, unsigned);
extern char D_002D4220[];

extern "C" int FMpegDecodeVideo__FP7sceMpegP13sceMpegCbDataP5CMpeg(sceMpeg *, sceMpegCbData *, CMpeg *pmpeg)
{
    int work[16];

    while (pmpeg->qVideo.cbData <= 0xfff) {
        int result = CMpeg_CbDemuxed(pmpeg, 1);
        if (result == 2) {
            memset(work, 0, 0x40);
            pmpeg->qVideo.CbFill(0x40 - (pmpeg->qVideo.cbData % 0x20), (u8 *)work);
            break;
        }
        if (result == 1)
            pmpeg->audio.Update();
    }
    work[0] = (sptr)D_002D4220;
    pmpeg->qVideo.FreeDrain(0);
    pmpeg->qVideo.CbDrain(0, (CQueueOutput *)work);
    return 1;
}
