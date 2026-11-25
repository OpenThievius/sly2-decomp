/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
#include "cmpeg.h"
extern "C" {
extern int B_002E1E54;
extern int g_2dedbc;
int CMpeg_CbDemuxed(CMpeg *, int);
int sceMpegInit();
void sceMpegCreate(void *, int, int);
void sceMpegAddStrCallback(void *, int, int, void *, CMpeg *);
void sceMpegAddCallback(void *, int, void *, CMpeg *);
void FMpegAcceptVideo__FP7sceMpegP16sceMpegCbDataStrP5CMpeg();
void FMpegAcceptAudio__FP7sceMpegP16sceMpegCbDataStrP5CMpeg();
void FMpegDecodeVideo__FP7sceMpegP13sceMpegCbDataP5CMpeg();
void FMpegBackground();
void func_001B3508();
}
void CMpeg_Start(CMpeg *mpeg, CBinaryAsyncStream *pbas)
{
    mpeg->pbas = pbas;
    mpeg->tPicture = 0;
    void *sdk = mpeg->sdk;
    mpeg->qVideo.Init(0x40000, (void *)((sptr)(mpeg->pbBuffer + 0x245A80) | 0x20000000));
    mpeg->audio.Init();
    sceMpegInit();
    sceMpegCreate(sdk, (sptr)(mpeg->pbBuffer + 0x98000), 0x1ADA60);
    sceMpegAddStrCallback(sdk, 0, 0, (void *)FMpegAcceptVideo__FP7sceMpegP16sceMpegCbDataStrP5CMpeg, mpeg);
    sceMpegAddStrCallback(sdk, 2, 0, (void *)FMpegAcceptAudio__FP7sceMpegP16sceMpegCbDataStrP5CMpeg, mpeg);
    sceMpegAddStrCallback(sdk, 3, 0, (void *)FMpegAcceptAudio__FP7sceMpegP16sceMpegCbDataStrP5CMpeg, mpeg);
    sceMpegAddStrCallback(sdk, 2, B_002E1E54 + 1, (void *)FMpegAcceptAudio__FP7sceMpegP16sceMpegCbDataStrP5CMpeg, mpeg);
    sceMpegAddStrCallback(sdk, 3, B_002E1E54 + 1, (void *)FMpegAcceptAudio__FP7sceMpegP16sceMpegCbDataStrP5CMpeg, mpeg);
    sceMpegAddCallback(sdk, 1, (void *)FMpegDecodeVideo__FP7sceMpegP13sceMpegCbDataP5CMpeg, mpeg);
    sceMpegAddCallback(sdk, 4, (void *)FMpegBackground, mpeg);
    sceMpegAddCallback(sdk, 0, (void *)func_001B3508, mpeg);
    int done;
    do {
        done = CMpeg_CbDemuxed(mpeg, 1);
    } while (done == 0);
    g_2dedbc = 0;
}
