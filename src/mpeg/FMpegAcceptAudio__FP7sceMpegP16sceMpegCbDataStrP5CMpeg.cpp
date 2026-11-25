#include "cmpeg.h"
extern "C" int FMpegAcceptAudio__FP7sceMpegP16sceMpegCbDataStrP5CMpeg(sceMpeg *, sceMpegCbDataStr *cb, CMpeg *mpeg) {
    return mpeg->audio.FAccept(cb->size, cb->data);
}
