// SPDX-License-Identifier: GPL-3.0-or-later
/* 0x1B3388: FMpegAcceptVideo: accept when the video queue has room for the chunk size; fill it from the chunk's data */
#include "cmpeg.h"
extern "C" s32 FMpegAcceptVideo__FP7sceMpegP16sceMpegCbDataStrP5CMpeg(sceMpeg *, sceMpegCbDataStr *pcbdata, CMpeg *pmpeg) {
    u32 size = pcbdata->size;
    if (pmpeg->qVideo.cbFree < size) {
        return 0;
    }
    pmpeg->qVideo.CbFill(size, pcbdata->data);
    return 1;
}
